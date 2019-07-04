import scala.io.StdIn
import scala.io.Source

//IO CODE
//Pledged: this assignment is entirely my own work

println("The program takes 32 bit binary strings and returns the corresponding MIPS instruction. Please enter a file name that contains 32 bit binary strings:")

val input = scala.io.StdIn.readLine()

println()
println()
println("RESULT:  ")
val lines = Source.fromFile(input).getLines.toList

for(line <- lines){
   println("Binary: " + line + "\n")
    
   println("MIPS: "+ binaryTranslate(line) + "\n\n")
}

//Binary Translate Function

def binaryTranslate(binaryString:String):String = {

val functR = Map("100000"->"add",100001->"addu","100100"->"and","100111"->"nor","100101"->"or", "000000"->"sll","000100"->"sllv","101010"->"slt","101011"->"sltu","000011"->"sra","000111"->"srav", "000010"->"srl", "srlv"->"000110", "100010"->"sub","100011"->"subu","100110"->"xor","001000"->"jr")

val instructionI = Map("001000"->"addi", "001001"->"addiu", "001101"->"ori", "001010"->"slti", "001011"->"sltiu", "001110"->"xori", "001111"->"lui", "001100"->"andi", "100011"->"lw","101011"->"sw")


val instructionBranch = Map("000100"->"beq","000001"->"bgez", "000111"->"bgtz", "000110"->"blez", "000101"->"bne") 


val instructionJ = Map("000010"->"j","000011"->"jal")


val mipsRegisters = Map("00000"->"zero","00001"->"at", "00010"->"v0", "00011"->"v1", "00100"->"a0", "00101"->"a1", "00110"->"a2", "00111"->"a3", "01000"->"t0", "01001"->"t1", "01010"->"t2", "01011"->"t3", "01100"->"t4", "01101"->"t5", "01110"->"t6", "01111"->"t7","10000"->"s0", "10001"->"s1", "10010"->"s2", "10011"->"s3", "10100"->"s4", "10101"->"s5", "10110"->"s6", "10111"->"s7", "11000"->"t8", "11001"->"t9", "11100"->"gp", "11101"->"sp", "11110"->"fp", "11111"->"ra")

 
val opcode:String = binaryString.take(6)
var rs:String = ""
var rt:String = ""
var rd:String = ""

    if(binaryString.length != 32) return("Error: not enough digits"); 
    
    if(!(binaryString.contains("0")) || !(binaryString.contains("1"))) return("Error: only binary digits accepted"); 

    if(opcode=="000000"){

       rs = binaryString.drop(6).take(5) 
       rt = binaryString.drop(11).take(5) 
       rd = binaryString.drop(16).take(5)  
       val funct = binaryString.drop(26)

        if(funct == "001000"){
           rs = binaryString.drop(6).take(5)
           return(functR(funct) + " $" + mipsRegisters(rs))   
        }
        else if(funct=="000100" || funct =="000010" || funct =="000011" || funct == "000000"){
           //There is no rd. It is replaced by shiftAmount.  
 
           val shiftAmount = Integer.parseInt(binaryString.drop(16).take(5),2)
           return (functR(funct) + " $" + mipsRegisters(rs) + ", $" + mipsRegisters(rt)+", " + shiftAmount )  
              
        }
        else {       
       return (functR(funct) +"  $" + mipsRegisters(rs) + ", $" + mipsRegisters(rt) + ", $" + mipsRegisters(rd))     
       }

    }

    else if (instructionI.contains(opcode)){
         
        rs = binaryString.drop(6).take(5) 
        rt = binaryString.drop(11).take(5)

 
         if(opcode == "100011" || opcode == "101011"){
             var offset:String = ""
             val base = binaryString.drop(6).take(5) 
             val addressBinary = binaryString.drop(16)
           for(i<-3 to addressBinary.length-1 by 4){
                 
              var takeFour:String = addressBinary(i-3).toString + addressBinary(i-2).toString + addressBinary(i-1).toString+addressBinary(i).toString
              offset = offset.concat(Integer.parseInt(takeFour,2).toHexString)
           }   
           
           return (instructionI(opcode) + " $" + mipsRegisters(rt) + ", 0x" + offset + "($" + mipsRegisters(base)+")")  
//offset(base)  
         }
        else{ 
             val immediateValue = Integer.parseInt(binaryString.drop(16),2)
             return (instructionI(opcode) + " $" + mipsRegisters(rs) + ", $" + mipsRegisters(rt) + ", "+ immediateValue )
       }        
    }



   else if(instructionBranch.contains(opcode)){
      var hexAddress:String = ""
          rs = binaryString.drop(6).take(5) 
          rt = binaryString.drop(11).take(5) 
      val addressBinary = binaryString.drop(16)
      for(i<- 3 to addressBinary.length-1 by 4){

      var takeFour:String = addressBinary(i-3).toString + addressBinary(i-2).toString + addressBinary(i-1).toString+addressBinary(i).toString
      hexAddress = hexAddress.concat(Integer.parseInt(takeFour,2).toHexString)
      }

      return (instructionBranch(opcode) + " $" + mipsRegisters(rs) + ", $" + mipsRegisters(rt) + ", 0x" + hexAddress)
      
   }

    else{
        var hexAddress:String = ""
        val addressBinary = binaryString.drop(6)
        for(i <- 3 to addressBinary.length-1 by 4){
          var takeFour:String = addressBinary(i-3).toString + addressBinary(i-2).toString + addressBinary(i-1).toString+addressBinary(i).toString
          var tmp =  (Integer.parseInt(takeFour,2))*4
          hexAddress = hexAddress.concat(tmp.toHexString) 
          //Use hexAddress.concat()  
        }
        return (instructionJ(opcode)+" 0x" + hexAddress)

    }
}

//Integer.parseInt !!
