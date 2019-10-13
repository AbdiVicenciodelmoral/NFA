java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.Scanner;
import java.io.File;
import java.util.Stack;

public class Automata {

    public static class transitions{
        int Cstate;
        int Nstate;
        int Nstate2;
        char symbol;
        transitions Tlist;
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
        //Create a transition class
        transitions tran = new transitions();
        tran.Cstate = NFA1.Estate;
        tran.Nstate = NFA2.Sstate;
        tran.symbol = 'E';
        //Create a temp Transition class to iterate
        //through the transitions
        transitions tmpTran = new transitions();
        tmpTran = NFA1.TList;
        while (tmpTran != null) {
            if(tmpTran.Tlist == null){
                break;
            }
            tmpTran = tmpTran.Tlist;
        }
        //Connect the transitions
        tmpTran.Tlist = tran;
        transitions tr = NFA2.TList;
        tmpTran.Tlist.Tlist = tr;
        //Connect the transition list to NFA1
        NFA1.Estate = NFA2.Estate;


        return NFA1;
    }

    public static NFA STAR(NFA oldNFA,int num){
        NFA starNFA = new NFA();
        starNFA.Sstate = num;
        starNFA.Estate = num;

        transitions tr = new transitions();
        tr.Cstate = starNFA.Sstate;
        tr.Nstate = oldNFA.Sstate;
        tr.symbol = 'E';
        tr.Tlist = oldNFA.TList;

        transitions tempTran = new transitions();
        tempTran = oldNFA.TList;
        while (tempTran != null) {
            if(tempTran.Tlist == null){
                break;
            }
            tempTran = tempTran.Tlist;
        }

        transitions lastTr = new transitions();
        lastTr.Cstate = tempTran.Nstate;
        lastTr.Nstate = starNFA.Sstate;
        lastTr.symbol = 'E';

        tempTran.Tlist = lastTr;
        starNFA.TList = tr;
        return starNFA;
    }

    public static NFA OR(NFA NFA1,NFA NFA2, int num){
        NFA orNFA = new NFA();
        orNFA.Sstate = num;
        orNFA.Estate = num+1;

        transitions firstTr = new transitions();
        firstTr.Cstate = orNFA.Sstate;
        firstTr.symbol = 'E';
        firstTr.Nstate = NFA1.Sstate;
        firstTr.Nstate2 = NFA2.Sstate;
        orNFA.TList = firstTr;
        transitions NFA1Tran = new transitions();
        NFA1Tran = NFA1.TList;
        while (NFA1Tran != null) {
            if(NFA1Tran.Tlist == null){
                break;
            }
            NFA1Tran = NFA1Tran.Tlist;
        }
        transitions NFA2Tran = new transitions();
        NFA2Tran = NFA2.TList;
        while (NFA2Tran != null) {
            if(NFA2Tran.Tlist == null){
                break;
            }
            NFA2Tran = NFA2Tran.Tlist;
        }

        transitions N1Epsilon = new transitions();
        N1Epsilon.Cstate = NFA1.Estate;
        N1Epsilon.Nstate = orNFA.Estate;
        N1Epsilon.symbol = 'E';

        transitions N2Epsilon = new transitions();
        N2Epsilon.Cstate = NFA2.Estate;
        N2Epsilon.Nstate = orNFA.Estate;
        N2Epsilon.symbol = 'E';

        //orNFA.TList = firstTr;
        NFA1Tran.Tlist = N1Epsilon;
        NFA2Tran.Tlist = N2Epsilon;
        NFA1Tran.Tlist.Tlist = NFA2.TList;
        orNFA.TList.Tlist = NFA1.TList;

        return orNFA;
    }




    public static void main(String args[]) throws FileNotFoundException {
        int count = 0;

        File infile = new File("src/SampleTestfile.txt");
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
                    NFA NFA2 = stack.pop();
                    NFA NFA1 = stack.pop();
                    stack.push(OR(NFA1, NFA2,num));
                    num++;
                    num++;
                }
                else if (c.equals('*')) {


                    NFA NFA1 = stack.pop();
                    stack.push(STAR(NFA1, num));
                    num++;
                    //push(NFA that accepts L(nFA) star);
                    //printf("TEST \n");
                    //printf("Letter:%i",c);
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

            NFA getBack = stack.pop();
            System.out.println("Count: "+count);
            count++;
            if(getBack.TList.Nstate2 != 0){
                System.out.format("S(q%d,%c)-> q%d,q%d \n",getBack.TList.Cstate, getBack.TList.symbol ,getBack.TList.Nstate,getBack.TList.Nstate2);
            }
            else{
                System.out.format("S(q%d,%c)-> q%d \n",getBack.TList.Cstate,getBack.TList.symbol,getBack.TList.Nstate);
            }
            getBack.TList = getBack.TList.Tlist;
            while(getBack.TList != null){
                if(getBack.TList.Nstate2 != 0){
                    System.out.format("(q%d,%c)-> q%d,q%d \n",getBack.TList.Cstate,getBack.TList.symbol,getBack.TList.Nstate,getBack.TList.Nstate2);
                }
                else if(getBack.TList.Nstate == getBack.Estate){
                    System.out.format("F(q%d,%c)-> q%d \n",getBack.TList.Cstate,getBack.TList.symbol,getBack.TList.Nstate);
                }
                else{
                    System.out.format("(q%d,%c)-> q%d \n",getBack.TList.Cstate,getBack.TList.symbol,getBack.TList.Nstate);
                }

                getBack.TList = getBack.TList.Tlist;
            }
            System.out.println("_____________________________________________________________________________________________");
        }


        input.close();

    }
}
