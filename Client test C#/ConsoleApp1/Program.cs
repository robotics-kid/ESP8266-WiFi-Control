using System;
using System.IO;
using System.Net;
using System.Text;
using System.Net.Sockets;


public class clnt
{

    public static void Main()
    {

        try
        {
            //FoViBalTLight;EFF:1;HUE:0;SAT:255;VAL:0;WHT:0
            TcpClient tcpclnt = new TcpClient();
            Console.WriteLine("Connecting.....");

            tcpclnt.Connect("192.168.4.1", 80);
            // use the ipaddress as in the server program

            Console.WriteLine("Connected");
            Console.Write("Enter the string to be transmitted : ");

            String str = Console.ReadLine();
            Stream stm = tcpclnt.GetStream();
            str += '\n';

            ASCIIEncoding asen = new ASCIIEncoding();
            byte[] send = asen.GetBytes(str);
            Console.WriteLine("Transmitting.....");
            Console.WriteLine("send: ");

            for (int i = 0; i < str.Length; i++)
                Console.Write(Convert.ToChar(send[i]));
            Console.WriteLine();

            stm.Write(send, 0, send.Length);

            byte[] recv = new byte[1024];
            int recievedDateLength = stm.Read(recv, 0, 1024);

            for (int i = 0; i < recievedDateLength; i++)
                Console.Write(Convert.ToChar(recv[i]));
            
            tcpclnt.Close();
        }

        catch (Exception e)
        {
            Console.WriteLine("Error..... " + e.StackTrace);
        }
    }

}