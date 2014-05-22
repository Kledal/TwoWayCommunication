using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace prisonSystem
{
    class Slave
    {
        private string _addr;
        private string _state;
        private string _name;
        private DateTime _lastMessage;

        private bool _requested_state = false;
        private bool _alarm = false;

        public Slave(string addr, string name, string state)
        {
            _lastMessage = DateTime.Now;
            _addr = addr;
            _name = name;
            _state = state;
        }

        public void SendMessage(CMD message)
        {
            if (!ReadyNextMsg())
            {
                Program.WriteLog("Slave is not ready for next message yet.");
                return;
            }

            _lastMessage = DateTime.Now;
            string cmd = Program._commands[(int)CMD.StartBit] + _addr + Program._commands[(int)message];
            Program.commandqueue.Push(cmd);

            _alarm = false;

            if (message == CMD.Status)
                _requested_state = true;
        }

        public void SetState(string state)
        {
            if (!RequestedNewState && state != State)
            {
                _alarm = true;
            }
            _state = state;
            _requested_state = false;
        }

        public string Address { get { return _addr; } }
        public string State { get { return _state; } }
        public string Name { get { return _name; } }
        public bool RequestedNewState { get { return _requested_state;} }
        public bool Alarm { get { return _alarm; } }
        public bool ReadyNextMsg() {
            return (_lastMessage < DateTime.Now.AddSeconds(4));
        }
    }
}
