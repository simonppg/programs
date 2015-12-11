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
        ServerSocket s=null;
        int a,b,result;
        try
        {
            s= new ServerSocket(5432);	// nuevo socket a la escucha por el puerto espesificado
        }
        catch (IOException e)
        {
            e.printStackTrace();
        }
        while(true)
        {
            try
            {
                Socket s1 = s.accept();
                DataInputStream dis = new DataInputStream(s1.getInputStream());
                a=dis.readInt();
                b=dis.readInt();
                OutputStream slout = s1.getOutputStream();
                BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(slout));
                result=a+b;
                bw.write(result);
                result=a-b;
                bw.write(result);
                result=a*b;
                bw.write(result);
                result=a/b;
                bw.write(result);
                bw.close();
                s1.close();
            }
            catch(IOException e)
            {
                e.printStackTrace();
            }
        }
    }
}

