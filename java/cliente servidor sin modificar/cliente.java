/** Nombre: SimpleCliente.java
*autor: MALM...
*/

import java.net.*;
import java.io.*;

public class cliente
{
    public static void main(String args[]) throws IOException
    {
        int c,con;
        int a=4,b=4;
        String avisos []={"LA SUMA de 4 y 4 ES: ","LA RESTA de 4 y 4 ES: ","LA MULTIPLICACION de 4 y 4 es: ","LA DIVISION de 4 y 4 es: "};
        try
        {
            Socket s1 = new Socket("localhost",5432);
            InputStream is = s1.getInputStream();
            DataOutputStream dos = new DataOutputStream(s1.getOutputStream());
            dos.writeInt(a);
            dos.writeInt(b);
            con=0;
            DataInputStream dis = new DataInputStream(is);
            while((c=dis.read())!=-1)
            {
                System.out.println(avisos[con]);
                System.out.println(Math.round((double)c));
                con++;
            }
            s1.close();
            dis.close();
        }
        catch (ConnectException connExc)
        {
            System.err.println("OCURRIO UN ERROR");
        }
        catch (IOException e)
        {
        }
    }
}
