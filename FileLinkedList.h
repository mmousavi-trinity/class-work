template<typename T>
class FileLinkedList {
        FileLinkedList(const FileLinkedList<T> &that) = delete;
        FileLinkedList<T> operator=(const FileLinkedList<T> &that) = delete;
	

    private:
           FILE* file; 
           int first;
           int sz;  
 	   struct Node{
  	          T data;
                  int prev;
  		  int next;
		    };
        
            void WriteSize(){
                 std::fseek(file,0, SEEK_SET); 
                 std::fwrite(&sz,sizeof(int),1,file);

        }   
            
           void WriteFirst(){
                 std::fseek(file,sizeof(int), SEEK_SET);
                 std::fwrite(&first,sizeof(int),1,file); 


        }
            int ReadPrev(int node, FILE* file){
                 fseek(file,node+sizeof(T)  , SEEK_SET);
                 int ret;
                 fread(&ret, sizeof(int), 1, file );
                 return ret;
        }
            void WritePrev(int node,int value, FILE* file){
                 fseek(file,node+sizeof(T), SEEK_SET);
                 fwrite(&value, sizeof(int), 1, file );
        }
            int ReadNext(int node, FILE* file){
                 fseek(file,node+ sizeof(T)+sizeof(int) ,SEEK_SET);
                 int ret;
                 fread(&ret, sizeof(int), 1, file );
                 return ret;
        }
            void WriteNext(int node, int value, FILE* file){
                 fseek(file,node+ sizeof(T)+sizeof(int) ,SEEK_SET);
                 fwrite(&value, sizeof(int), 1, file );
        }

            T ReadData(int node, FILE* file){
                 fseek(file, node, SEEK_SET);
                 T ret;
                 fread(&ret, sizeof(T), 1, file );
                 return ret;

        }
            void WriteData(int node, T value, FILE* file){
                 fseek(file, node, SEEK_SET);
                 fwrite(&value, sizeof(T), 1, file );
        } 
            int AllocateNode(FILE* file, int sz){
    //read freelist
                 fseek(file, sizeof(Node), SEEK_SET);
                 int freelist;
                 fread(&freelist, sizeof(int), 1, file);
                 int ret;
               if (freelist != -1){
                ret=freelist;
               	freelist = ReadNext(freelist, file);
	//write freelist
         	fseek(file, sizeof(Node), SEEK_SET);
        	fwrite(&freelist, sizeof(int), 1, file);
              }  
               else{
	        ret=sizeof(Node)+2*sizeof(int)+ sz* sizeof(Node);
              }
                return ret;
        }
   void DeallocateNode(int node, FILE* file){
      //read freelist
      fseek(file, sizeof(Node), SEEK_SET);
      int freelist;
      fread(&freelist, sizeof(int), 1, file);

      WriteNext (node, freelist, file);
      freelist=node;
      fseek(file, sizeof(Node), SEEK_SET);
      fwrite(&freelist, sizeof(int), 1, file);
     } 

     int newNode (){
        if (first == -1) {
           return sz+1; 
        }  else {
           int tmp = first;
           first = ReadNext(first);
           WriteFirst(); 
           return tmp; 
        }
      void freeNode (int l){
         WriteNext(l,first); 
         first = l; 
         WriteFirst(); 



        }             
        // TODO - Private helper functions. (Maybe file IO with an index.)
    public:
        typedef T value_type;

        class const_iterator {
           private: 
                FILE* ptr; 
                int index; 
            public:
                const_iterator(int i,FILE *f){
                 index = i;
                 ptr = f;    
                }
                const_iterator(const const_iterator &i){
                 index = i.index;
                 ptr = i.ptr;
                }
                T operator*(){
                   return read(ptr,index);
                }
                bool operator==(const const_iterator &i) const{
                     return (index == i.index && ptr==i.ptr); 
                }
                bool operator!=(const const_iterator &i) const{
                     return (index != i.index || ptr != i.ptr); 
                }
                const_iterator &operator=(const const_iterator &i){
                   ptr = i.ptr; 
                   index = i.index;
                   return *this;  
                }
                const_iterator &operator++(){
                   ++index;
                   return *this; 
                }
                const_iterator &operator--(){
                   --index; 
                   return *this; 
                }
                const_iterator operator++(int){
                   const_iterator tmp = *this; 
                   ++index; 
                   return tmp;
                }
                const_iterator operator--(int){
                   const_iterator tmp = *this; 
                   ++index; 
                   return tmp; 
                } 
                friend class FileLinkedList;
        };
        sz = 0;
        // General Methods
        FileLinkedList(const std::string &fname){
           auto file = fopen(fname.c_str(),"rb+");
           if(file == nullptr){
              file = fopen(fname.c_str(), "wb+");
              first = -1; 
              sz = 0; 
              WriteSize(); 
              WriteFirst(); 
              WritePrev(0,0); 
              WriteNext(0,0); 
             } 
           else{
              fread(&sz,sizeof(int),1,file);
           } 
        }
        template<typename I>  // The type I will be an iterator.
        FileLinkedList(I begin,I end,const std::string &fname) { 
            file = fopen(fname.c_str(), "wb+");// TODO - Write this one here. It is easier than trying to fight with adding a template below.
	    int tempA = 1; 
            sz = 0; 
            first = -1; 
            WriteNext (0,1);
             for (auto a = begin; a != end; ++a) {
                 int tempB = tempA +1; 
                 WriteData(tempA, *a, file) 
                 WriteNext(tempA, tempB,file); 
                 WritePrev(tempA, tempA-1 , file); 
                 tempA = tempB; 
                ++sz;  
        }
           WriteNext(tempA-1,0,file); 
           WritePrev(0,sz); 
           WriteSize(); 
           WriteFirst(); 
        }

        ~FileLinkedList(){
           fclose(file);
       }
        void push_back(const T &t) {
           int l = newNode(); 
           WriteNode(l,ReadPrev(0), 0,t); 
           WriteNext(ReadPrev(0), l,file); 
           WritePrev(0, l); 
           ++sz; 
           WriteSize();
       }
        void pop_back() { erase(--end()); }
        int size() const{
          return sz; 
       }
        void clear() { while (size()>0) pop_back(); }

        const_iterator insert(const_iterator position, const T &t){
           int l; 
           if(first>0){ 
           WriteData(first,t,file); 
           WritePrev(first,ReadPrev(position.index),file); 
           int newF = ReadNext(first); 
           WriteNext(first, position.index, file); 
           WriteNext(ReadPrev(position.index), first); 
           WritePrev(position.index,first,file);
           first = newF; 
       } 
          else {
           l = sz+1; 
           WriteData(sz+1,t,file); 
           WritePrev(sz+1,ReadPrev(position.index),file);
           WriteNext(sz+1,position.index,file); 
           WriteNext(ReadPrev(position.index), sz+1, file); 
           WritePrev(position.index, sz+1); 
         }
        ++sz;
        WriteSize(); 
        WriteFirst(); 
        return const_iterator(loc,file);            




      }
        T operator[](int index) const{
            auto itr=begin();
            for (int i=0;i<index;++i) ++itr;
            return *itr;
        }
        const_iterator erase(const_iterator position){
             int newF = position.index; 
             int returnNext = ReadNext(newF); 
             WriteNext(ReadPrev(newF), ReadNext(newF)); 
             WritePrev(ReadNext(newF), ReadNext(newF)); 
             WriteNext(newF, first); 
             first = newF; 
             --sz; 
             WriteSize(); 
             WriteFirst(); 
             return const_iterator(returnNext,file);  
       

        }
        void set(const T &value,int index){
              const_iterator temp = begin(); 
              for(int a = 0; a!=index; ++a){
                 temp++; 
        }
              WriteData(temp.index,value); 

       }
        void set(const T &value,const_iterator position){
             WriteData(position.index,value,file); 
       
        } 
        const_iterator begin(){
             return const_iterator(0,file); 
        }
        const_iterator begin() const{
             return const_iterator(readNext(0,file),file); 
        }
        const_iterator end();{
             return const_iterator(0,file); 
        }
        const_iterator end() const;
             return const_iterator(readNext(0,file),file); 

        const_iterator cbegin() const{
             return const_iterator(readNext(0,file),file); 
        }
        const_iterator cend() const;
             return const_iterator(0,file); 
};

