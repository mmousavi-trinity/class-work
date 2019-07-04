
template<typename K,typename V>
class BSTMap {

private: 
    struct node {
       node* parent; 
       node* left; 
       node* right;
       std::pair<K,V> value;  
    };
     int sz; 
public:
    typedef K key_type;
    typedef V mapped_type;
    typedef std::pair<K,V> value_type;

    class const_iterator;

    class iterator {

    private:     
          node* ptr;  
          bool flag; 
        // TODO: Iterator data. 
        //Need to be able to go back from end, i.e. --end() should 
        //give last element.
        //One approach is to keep a Node* and a bool that tells me if 
        //it is at end.
        //If just keeping Node* and use nullptr to indicate end(), then
        //operator-- need a case for nullptr, in which case to get the 
        //maximum element. But to get the maximum element, we need to 
        //store information about the tree, e.g. the root pointer, as member.
    public:
        friend class const_iterator;
        iterator(node* n,bool f)/*:...*/ {
             ptr = n;
             flag = f; 

        }
        // TODO: Other constructors as needed.

        bool operator==(const iterator &i) const { return (*this==i);}
        bool operator!=(const iterator &i) const { return !(*this==i); }
        std::pair<K,V> &operator*() {return ptr->value;}
        iterator &operator++() {
            if (*ptr->right != nullptr)
            return minimum(*ptr->right);
            else {
               if (*ptr == *ptr->parent->left) ptr = ptr->parent;
               else ptr = ptr->parent->parent; 
            } 
            return *this;
        }
        iterator &operator--() {
            if (ptr->left!=nullptr){
                ptr = ptr->left;  
                return *this
            }      // check boolean; if false, then return predecessor. 
        }
        iterator operator++(int) {
            iterator tmp(*this);
            ++(*this);
            return tmp;
        }
        iterator operator--(int) {
            iterator tmp(*this);
            --(*this);
            return tmp;
        }
    };

    class const_iterator {
          node* ptr;
          bool flag; 
    public:
        friend class BSTMap<K,V>;  // You might not need this in your code, but it helped me.
        const_iterator(node* n, bool f )/*:...*/ {
            ptr = n; 
            flag = f;

         }
        // TODO: Other constructors as needed.
        const_iterator(const iterator &iter) {
                   *this = iter; 
                   return *this; 

         }

        bool operator==(const const_iterator &i) const { return (*this==i)  }
        bool operator!=(const const_iterator &i) const { return(*this!=i) }
        const std::pair<K,V> &operator*() { return ptr->value  }
        const_iterator &operator++() {
             if (*ptr->right != nullptr)
            return minimum(*ptr->right);
            else {
               if (*ptr == *ptr->parent->left) ptr = ptr->parent;
               else ptr = ptr->parent->parent; 
            } 
            return *this;
        }
        const_iterator &operator--() {
            if(ptr==nullptr){
            ptr = maximum(*ptr);
            }
            else{
                ptr = --(*ptr); 
                return *this;
        }
        const_iterator operator++(int) {
            const_iterator tmp(*this);
            ++(*this);
            return tmp;
        }
        const_iterator operator--(int) {
            const_iterator tmp(*this);
            --(*this);
            return tmp;
        }
    };



    BSTMap() {
        sz = 0; 
        auto* root = new Node = nullptr;
        root->parent=nullptr; 
    }
    ~BSTMap() {
        clear(); 
    }
    BSTMap(const BSTMap<K,V> &that) {
        sz = 0; 
        auto* root = new Node;
        root ->parent = nullptr;  
    }

    BSTMap &operator=(const BSTMap<K,V> &that) {
        clear(); 
        for(auto x:that){
        insert(x); 
       }
        return *this; 
    }; 

    iterator minimum(node* x){
       while (x->left != nullptr){
             x = x->left;
       }
             return find(x); 
    }  
    iterator maximum(node* x){
       auto temp = x->parent;
       if (x->right != nullptr){
       while (x->right != nullptr){
              x = x->right; 
              return find(x);
       }
      }
       else x->right = temp;  
    }
    bool empty() const { return size() == 0; }

    unsigned size() const { return sz; }

    iterator find(const key_type& k){
            auto p = root; 
            if (sz ==0) { return end();}
          
          if(p != end()){   
            while (p->data.first != k){
            if (p->right != nullptr && p->data.first < k) {
                p=p->right; 
             }
            else if (p->right != nullptr && p->data.first > k){        
                p=p->left;
            }
           } 
            return iterator(p);  
      }
          else return iterator(end); 
     }
    }

    const_iterator find(const key_type& k) const{
            auto p = root; 
           if sz ==0 { return end();}
          
           if(p != end()){   
            while (p->data.first != k){
            if (p->right != nullptr && p->data.first < k) {
                p=p->right; 
             }
            else if (p->right != nullptr && p->data.first > k){        
                p=p->left;
            }
           } 
            return const_iterator(p);  
       }
          else return const_iterator(end); 
     }
    unsigned int count(const key_type& k) const { 
        if(find(k)!=cend()) return 1;
        else return 0;
    }

    std::pair<iterator,bool> insert(const value_type& val){
        auto* f = find(val.first)
        auto* temp = new Node; 
        temp->right = nullptr; 
        temp->left = nullptr; 
        auto* current = root; 
        temp->value = val;
        s = false; 
      while (s == false) { 
        if(root == nullptr){
           root = temp;
           temp->parent = nullptr;  
           return std::make_pair(iterator(temp),true); 
           s=true; 
        }
        else {
          if(temp->val.first < current->value.first){    
              if (root->left == nullptr){
                  current->left = temp;
                  temp->parent = current;                    
                  return std::make_pair(iterator(temp),true);
                  s=true; 
              }
              else  
                  current = current->left; 
           }
         }
          else if (temp->val.first > current->value.first){
              if(root->right == nullptr){
                 current->right = temp;
                 temp->parent = current; 
                 return std::make_pair(iterator(temp),true);
                 s=true; 
              }
              else 
                  current = current->right;        
          }
          else return make_pair(iterator(temp,false), false);              
      }
    }
      
    }

    template <class InputIterator>{
    void insert(InputIterator first, InputIterator last);
          

    iterator erase(const_iterator position){
              auto* n = find((position));
                    l = *n->left;
                    r = *n->right; 
                    p = *n->parent;
              //no children 
              if (r == nullptr && l ==nullptr){
                 *n = nullptr; 
              }
              //One right child
              else if (l == nullptr) {
                   if(p==nullptr) *root=r;

                   else if (p->left == *n){ 
                            p->left=r;
                            r->parent=p; 
                   }
               
                   else if (p->right == *n)   { 
                            p->right=r;
                            l->parent=p;
                  }
                  *n=nullptr;
              }
              //One left child
              else if (r == nullptr){
                  if(p==nullptr) *root=l; 

                  else if (p->left == *n){
                           p->left=l; 
                           l->parent=p; 
                  }
                  else if (p->right == *n){
                           p->right=l; 
                           l->parent=p; 
                 }
                 *n=nullptr;
               }

             //2 children
              else if (r != nullptr && l != nullptr)
               {
                   auto* min = minimum(r);   
                    *n = *min;
                     erase(min);                  
                } 
                //  else if (p->left=*n){
                 //  auto* max = maximum(l); 
                 //  *n = *max; 
                  //  erase(max);
             
                //  auto tmp = *n->left->value; 
                //  *n->left = nullptr; 
                //  *n->value = tmp;                  
    }

    unsigned int erase(const key_type& k){
        const_iterator it = find(k);
        if (it!=cend()) {
            erase(it);
            return 1;
        }
        else {
            return 0;
        }
    }

    void clear(){
      for(auto i=begin();i!=end();i++){
             erase(i); 
      } 
    }

    mapped_type &operator[](const K &key){
        return (*insert(make_pair(key, V())).first).second;
    }

    bool operator==(const BSTMap<K,V>& rhs) const{ return (*this == rhs);}

    bool operator!=(const BSTMap<K,V>& rhs) const { return ! (*this == rhs); }

    iterator begin() { return iterator( minimum(root),true ); }

    const_iterator begin() const { return const_iterator(minimum(root),true); }

    iterator end() { return iterator((maximum(root)),false); }

    const_iterator end() const { return const_iterator(maximum(root),false); }

    const_iterator cbegin() const { return const_iterator(minimum(root),true); }

    const_iterator cend() const { return const_iterator(maximum(root),false); }

};
