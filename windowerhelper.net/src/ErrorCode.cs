namespace Windower
{
    public enum ErrorCode
    {
        None = 0x00,
        Unknown = 0x01,
        OutOfMemory = 0x02,
        InvalidArgument = 0x03,
        OutOfRange = 0x04,
        InvalidHandle = 0x05,
        ConnectionFault = 0x06,
        ConnectionClosed = 0x07,
        Interrupt = 0x08,
        InvalidReply = 0x09,
        NotFound = 0x0A,
        Encoding = 0x0B,
    }
}
