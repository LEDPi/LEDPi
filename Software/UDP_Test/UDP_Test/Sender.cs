using System;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using System.Linq;

namespace UDP_Test
{
    public class Sender
    {
        public Sender()
        {
            SendingPort = 0;
            PortReceiving = 0; 
            IPAdress = String.Empty;
        }
        
        public void Send(byte[] dataToSend)
        {
            var sender = new UdpClient(IPAdress,SendingPort);
            sender.Send(dataToSend, dataToSend.Length);
        }

        public String ReceiveMessageExpected(bool checkMessage = false)
        {
            String output;
            var receiver = new UdpClient(PortReceiving)
                {
                    Client = {ReceiveTimeout = 5000}
                };

            var remoteIpEndPoint = new IPEndPoint(IPAddress.Any, 0);

            try
            {
                var receivedData = receiver.Receive(ref remoteIpEndPoint);
                output = String.Join(" ", receivedData.Select(x => x.ToString("X2")).ToArray());
                
                if (checkMessage)
                {
                    var checkSum = (byte)((receivedData.Take(receivedData.Length - 1).Sum(x => x)) % 0xFF);
                    var length = (receivedData[2] << 8) + receivedData[3];

                    if (checkSum != receivedData[receivedData.Length - 1])
                    {
                        output += " |Checksum Error|";
                    }

                    if (length != (receivedData.Length - 5))
                    {
                        output += " |Length Error|";
                    }
                }
            }
            catch
            {
                output = "No response";
            }
            
            receiver.Close();
            return output;   
        }


        public byte CalculateChecksum(UInt16 functionCode, List<byte> bytes)
        {
            var useData = new Byte[bytes.Count];
            Array.Copy(bytes.ToArray(), 0, useData, 0, bytes.Count);

            var dataToSend = new byte[useData.Length + 5];
            dataToSend[0] = (byte)(functionCode >> 8);
            dataToSend[1] = (byte)(functionCode & 0xFF);
            dataToSend[2] = (byte) (useData.Length >> 8);
            dataToSend[3] = (byte) (useData.Length & 0xFF);
            useData.CopyTo(dataToSend, 4);

            byte checksum=0;

            for (int i = 0; i < useData.Length + 4; i++)
            {
                checksum = (byte)((checksum + dataToSend[i]) % 0xFF);}

            checksum %= 0xFF;

            return checksum;
        }

        public static byte[] BuildMessage(UInt16 functionCode, byte[] useData)
        {
            var dataToSend = new byte[useData.Length + 5];

            dataToSend[0] = (byte)(functionCode >> 8);
            dataToSend[1] = (byte)(functionCode & 0xFF);
            dataToSend[2] = (byte)(useData.Length >> 8);
            dataToSend[3] = (byte)(useData.Length & 0xFF);
            useData.CopyTo(dataToSend, 4);

            byte checksum=0;

            for (int i = 0; i < useData.Length + 4; i++)
            {
                checksum = (byte)((checksum + dataToSend[i]) % 0xFF);
            }

            dataToSend[dataToSend.Length - 1] = (byte)checksum;

            return dataToSend;
        }

        public int SendingPort { get; set; }
        public int PortReceiving { get; set; }
        public string IPAdress { get; set; }
    }
}
