import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.Scanner;
import java.io.File;
import java.util.Stack;

public class Automata {

    public static class transitions{
        int Cstate;
        int Nstate;
        char symbol;
        transitions Translist;
    }

    public static class  NFA{

        int Sstate;
        int Estate;
        transitions TList;
    }

    public static NFA nfaMaker(char c,int num){

        NFA newNFA = new NFA();
        transitions tlist = new transitions();
        newNFA.Sstate = num;
        num++;
        newNFA.Estate = num;
        num++;
        tlist.Cstate = newNFA.Sstate;
        tlist.Nstate = newNFA.Estate;
        tlist.symbol = c;
        newNFA.TList = tlist;
        //newNFA.TList.Nstate = newNFA.Estate;
        //newNFA.TList.symbol = c;

        return newNFA;
    }

    public static NFA And(NFA NFA1, NFA NFA2){
        NFA andNFA = new NFA();
        transitions tran = new transitions();
        transitions tranTran = new transitions();
        transitions tranTrantran = new transitions();

        andNFA.Sstate = NFA1.Sstate;
        andNFA.Estate = NFA2.Estate;
       
        tran.Cstate = NFA1.Sstate;
        tran.Nstate = NFA1.Estate;
        tran.symbol = NFA1.TList.symbol;
        andNFA.TList = tran;

        tranTran.Cstate = NFA1.Estate;
        tranTran.Nstate = NFA2.Sstate;
        tranTran.symbol = 'E';
        andNFA.TList.Translist = tranTran;

        tranTrantran.Cstate = NFA2.Sstate;
        tranTrantran.Nstate = NFA2.Estate;
        tranTrantran.symbol = NFA2.TList.symbol;
        andNFA.TList.Translist.Translist = tranTrantran;
        //transitions tranTran = new transitions();
       // tranTran.Cstate = NFA1.Estate;
        //tranTran.Nstate = NFA2.Sstate;
       // tranTran.symbol = 'E';
        //NFA1.Estate = NFA2.Estate;
        //NFA1.TList.Translist = tranTran;
        
        
        
        //System.out.println(NFA1.Sstate);
        //System.out.println(NFA1.Estate);
        //System.out.println(NFA1.TList.symbol);
        //System.out.println(NFA1.TList.Translist.Cstate);
        //System.out.println(NFA1.TList.Translist.Nstate);
        //System.out.println(NFA1.TList.Translist.symbol);
        return NFA1;
    }

    public static void main(String args[]) throws FileNotFoundException {
        //int num = 0;

        File infile = new File(args[0]);
        Scanner input = new Scanner(infile);
        Stack<NFA> stack = new Stack<NFA>();

        // System.out.println(input.next());
        //int i = 0;


        while(input.hasNext()){
            int num = 0;
            String reader = input.next();
            char [] holder = reader.toCharArray();

            for (Character c:holder) {


               // System.out.println(c);
                if (c.equals('&')) {
                    //nFA2 = pop();
                    //nFA1 = pop();
                    //push(NFA that accepts the concatenation of L(nFA1) followed by L(nFA2));
                    // printf("TEST & \n");
                    NFA NFA2 = stack.pop();
                    NFA NFA1 = stack.pop();
                    stack.push(And(NFA1, NFA2));
                    
                    
                }
                else if (c.equals('|')) {


                }
                else if (c.equals('*')) {

                    //nFA = pop();
                    //push(NFA that accepts L(nFA) star);
                    //printf("TEST \n");
                    //printf("Letter:%i",c);
                }
                else if( c == 13 || c == 10){
                    break;
                }
                else{

                    //nfaMaker(c,num);
                   // nfaMaker(c,num);
                    stack.push(nfaMaker(c,num));
                    num++;
                    num++;
                   // NFA test = stack.pop();
                    //System.out.println(test.Sstate);
                    //System.out.println(test.Estate);
                }
              

            }


        }


        input.close();

    }
}
