using System;
using System.IO;
using System.Net;
using System.Text;
using System.Net.Sockets;


public class clnt
{

    public static void Main()
    {
        UInt16 timeDelayed = 20;
        try
        {
            //FoViBalTLight;EFF:1;HUE:255;SAT:0;VAL:0;WHT:0!
            TcpClient tcpclnt = new TcpClient();
            Console.WriteLine("Connecting.....");

            tcpclnt.Connect("192.168.4.1", 80);
            // use the ipaddress as in the server program

            Console.WriteLine("Connected");
            //Console.Write("Enter the string to be transmitted : ");

            string str = "FoViBalTLight;EFF:1;HUE:255;SAT:0;VAL:0;WHT:0";
            Stream stm = tcpclnt.GetStream();

            ASCIIEncoding asen = new ASCIIEncoding();
            byte[] send = asen.GetBytes(str);
            byte[] send1 = asen.GetBytes("FoViBalTLight;EFF:1;HUE:0;SAT:255;VAL:0;WHT:0");
            Console.WriteLine("Transmitting.....");
            Console.WriteLine("send: ");
            System.Threading.Thread.Sleep(1000);
            while (true)
            {
                stm.Write(send, 0, send.Length);
                System.Threading.Thread.Sleep(timeDelayed);
                stm.Write(send1, 0, send1.Length);
                System.Threading.Thread.Sleep(timeDelayed);
            }

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