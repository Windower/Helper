namespace Windower
{
    using System;
    using System.Diagnostics;
    using System.Runtime.InteropServices;
    using System.Text;

    public sealed class Instance : IDisposable
    {
        internal static readonly Encoding ASCII = Encoding.GetEncoding("us-ascii", new EncoderExceptionFallback(), new DecoderExceptionFallback());
        internal static readonly Encoding UTF8 = Encoding.GetEncoding("utf-8", new EncoderExceptionFallback(), new DecoderExceptionFallback());

        private bool disposed = false;
        internal SafeInstanceHandle handle;

        public Instance(Process process)
        {
            NativeMethods.Initialize();

            if (process == null)
            {
                throw new ArgumentNullException("process");
            }

            WindowerException.Check(NativeMethods.windower_create(out this.handle, (uint)process.Id));
        }

        public Instance(string domain, Process process)
        {
            NativeMethods.Initialize();

            if (domain == null)
            {
                throw new ArgumentNullException("domain");
            }

            if (process == null)
            {
                throw new ArgumentNullException("process");
            }

            int utf8domainlength = UTF8.GetMaxByteCount(domain.Length) + 1;
            byte[] utf8domain = new byte[utf8domainlength];
            UTF8.GetBytes(domain, 0, domain.Length, utf8domain, 0);
            WindowerException.Check(NativeMethods.windower_create_remote(out this.handle, utf8domain, (uint)process.Id));
        }

        public Version Version
        {
            get
            {
                uint version;
                WindowerException.Check(NativeMethods.windower_get_version(this.handle, out version));
                return new Version((int)(version / 1000), (int)(version % 1000));
            }
        }

        internal SafeInstanceHandle Handle
        {
            get
            {
                return this.handle;
            }
        }

        public void Dispose()
        {
            if (!this.disposed)
            {
                this.handle.Dispose();
                this.disposed = true;
            }
        }

        public void SendString(string text)
        {
            if (text == null)
            {
                throw new ArgumentNullException("text");
            }

            int utf8textlength = Encoding.UTF8.GetMaxByteCount(text.Length) + 1;
            byte[] utf8text = new byte[utf8textlength];
            UTF8.GetBytes(text, 0, text.Length, utf8text, 0);
            WindowerException.Check(NativeMethods.windower_send_string(this.handle, utf8text));
        }

        public void SetKeyState(Key key, KeyState state)
        {
            WindowerException.Check(NativeMethods.windower_set_key_state(this.handle, key, state));
        }

        public void Block(InputKinds kind)
        {
            WindowerException.Check(NativeMethods.windower_block(this.handle, kind));
        }

        public void Unblock(InputKinds kind)
        {
            WindowerException.Check(NativeMethods.windower_unblock(this.handle, kind));
        }

        public string NextCommand()
        {
            SafeCommandHandle command = null;
            try
            {
                uint length;
                IntPtr ptr;
                WindowerException.Check(NativeMethods.windower_next_command(this.handle, out command));
                WindowerException.Check(NativeMethods.windower_command_length(command, out length));
                WindowerException.Check(NativeMethods.windower_command_string(command, out ptr));
                byte[] buffer = new byte[length];
                Marshal.Copy(ptr, buffer, 0, (int)length);
                return UTF8.GetString(buffer);
            }
            finally
            {
                if (command != null)
                {
                    command.Dispose();
                }
            }
        }
    }
}
