using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.IO.Ports;

namespace prisonSystem
{
    class Serial
    {
        private SerialPort _port;

        public event EventHandler dataReceived;

        public Serial(string comport = "COM5")
        {
            //this setup must be the same on STK500
            // set as 8 bit data, no parity bit and 1 stop bit.
            _port = new SerialPort(comport, 9600, Parity.None, 8, StopBits.One);
            _port.DataReceived += _port_DataReceived;
            _port.Open();
        }

        void SendData(string data)
        {
            if (!_port.IsOpen)
                return;
            _port.Write(data);
        }

        void _port_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            EventHandler handler = dataReceived;
            if (handler != null)
                handler(this, e);
        }

    }
}
