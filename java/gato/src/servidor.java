/** Nombre:Simple server.java
* Objetivo: Muestra como usar el cliente-servidor
* con java
* Fecha: 09/11/2007
*/

import java.net.*;
import java.io.*;

public class servidor
{
    public static void main(String args[])
    {
        ServerSocket s=null,s2=null;
        int a=0,b=0,result;
        int array[][];
        array=new int[3][3];
        for (int i=0;i<3;i++)
        {
            for (int j=0;j<3;j++)
            {
                array[i][j] = 0;
            }
        }
        for (int i=0;i<3;i++)
        {
            for (int j=0;j<3;j++)
            {
                System.out.print("Elemento:["+i+"]["+j+"]="+array[i][j]+"\t");
            }
            System.out.println("");

        }
        try
        {
            s= new ServerSocket(5432);
            //s2= new ServerSocket(5433);
        }
        catch (IOException e)
        {
            e.printStackTrace();
        }
        while(true)
        {
            try
            {
                Socket s1= s.accept();
                //Socket s3= s2.accept();
                DataInputStream dis = new DataInputStream(s1.getInputStream());
                //DataInputStream dis1 = new DataInputStream(s3.getInputStream());
                a=dis.readInt();
                b=dis.readChar();
                OutputStream slout = s1.getOutputStream();
                //OutputStream slout1 = s3.getOutputStream();
                BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(slout));
                //BufferedWriter bw1 = new BufferedWriter(new OutputStreamWriter(slout1));
                    //bw.write(b);
                System.out.println("Dato recibido: "+b);
                    System.out.println("Dato recibido: "+a);
                //result=a+b;
                //bw.write(result);
                //bw.close();
                //s1.close();
            }
            catch(IOException e)
            {
                e.printStackTrace();
            }
        }
    }
}

