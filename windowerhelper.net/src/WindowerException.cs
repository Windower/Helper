namespace Windower
{
    using System;
    using System.Runtime.Serialization;
    using System.Security.Permissions;

    [Serializable]
    public sealed class WindowerException : Exception
    {
        private ErrorCode error;

        public WindowerException()
        {
            this.error = ErrorCode.Unknown;
        }

        public WindowerException(string message)
            : base(message)
        {
            this.error = ErrorCode.Unknown;
        }

        public WindowerException(string message, Exception inner)
            : base(message, inner)
        {
            this.error = ErrorCode.Unknown;
        }

        public WindowerException(ErrorCode error)
            : base(GetMessage(error))
        {
            this.error = error;
        }

        public WindowerException(ErrorCode error, string message)
            : base(message)
        {
            this.error = error;
        }

        public WindowerException(ErrorCode error, Exception inner)
            : base(GetMessage(error), inner)
        {
            this.error = error;
        }

        public WindowerException(ErrorCode error, string message, Exception inner)
            : base(message, inner)
        {
            this.error = error;
        }

        internal WindowerException(SerializationInfo info, StreamingContext context)
            : base(info, context)
        {
            this.error = (ErrorCode)info.GetValue("Windower.WindowerException.Error", typeof(ErrorCode));
        }

        [SecurityPermission(SecurityAction.LinkDemand, Flags = SecurityPermissionFlag.SerializationFormatter)]
        public override void GetObjectData(SerializationInfo info, StreamingContext context)
        {
            base.GetObjectData(info, context);
            info.AddValue("Windower.WindowerException.Error", this.error, typeof(ErrorCode));
        }

        internal static void Check(ErrorCode error)
        {
            if (error != ErrorCode.None)
            {
                throw new WindowerException(error);
            }
        }

        private static string GetMessage(ErrorCode error)
        {
            switch (error)
            {
                default: return null;
                case ErrorCode.OutOfMemory: return "Out of Memory";
                case ErrorCode.InvalidArgument: return "Invalid Argument";
                case ErrorCode.OutOfRange: return "Out of Range";
                case ErrorCode.InvalidHandle: return "Invalid Handle";
                case ErrorCode.ConnectionFault: return "Connection Fault";
                case ErrorCode.ConnectionClosed: return "Connection Closed";
                case ErrorCode.Interrupt: return "Interrupted";
                case ErrorCode.InvalidReply: return "Invalid Reply";
                case ErrorCode.NotFound: return "Not Found";
                case ErrorCode.Encoding: return "Encoding";
            }
        }
    }
}
