namespace Windower
{
    using System.Diagnostics.CodeAnalysis;

    public enum Key
    {
        None = 0x00,

        Escape = 0x01,
        Enter = 0x1C,

        Insert = 0xD2,
        Delete = 0xD3,
        Home = 0xC7,
        End = 0xCF,
        PageUp = 0xC9,
        PageDown = 0xD1,

        LeftControl = 0x1D,
        LeftAlt = 0x38,
        LeftShift = 0x2A,
        RightControl = 0x9D,
        RightAlt = 0xB8,
        RightShift = 0x36,
        LeftWindows = 0xDB,
        RightWindows = 0xDC,
        AppMenu = 0xDD,

        F1 = 0x3B,
        F2 = 0x3C,
        F3 = 0x3D,
        F4 = 0x3E,
        F5 = 0x3F,
        F6 = 0x40,
        F7 = 0x41,
        F8 = 0x42,
        F9 = 0x43,
        F10 = 0x44,
        F11 = 0x57,
        F12 = 0x58,
        F13 = 0x64,
        F14 = 0x65,
        F15 = 0x66,

        PrintScreen = 0xB7,
        ScrollLock = 0x46,
        Break = 0xC5,

        Up = 0xC8,
        Down = 0xD0,
        Left = 0xCB,
        Right = 0xCD,

        [SuppressMessage("Microsoft.Naming", "CA1704", MessageId = "Num", Justification = "Named for consistancy with key naming conventions.")]
        NumLock = 0x45,

        [SuppressMessage("Microsoft.Naming", "CA1704", MessageId = "Num", Justification = "Named for consistancy with key naming conventions.")]
        NumPad0 = 0x52,
        [SuppressMessage("Microsoft.Naming", "CA1704", MessageId = "Num", Justification = "Named for consistancy with key naming conventions.")]
        NumPad1 = 0x4F,
        [SuppressMessage("Microsoft.Naming", "CA1704", MessageId = "Num", Justification = "Named for consistancy with key naming conventions.")]
        NumPad2 = 0x50,
        [SuppressMessage("Microsoft.Naming", "CA1704", MessageId = "Num", Justification = "Named for consistancy with key naming conventions.")]
        NumPad3 = 0x51,
        [SuppressMessage("Microsoft.Naming", "CA1704", MessageId = "Num", Justification = "Named for consistancy with key naming conventions.")]
        NumPad4 = 0x4B,
        [SuppressMessage("Microsoft.Naming", "CA1704", MessageId = "Num", Justification = "Named for consistancy with key naming conventions.")]
        NumPad5 = 0x4C,
        [SuppressMessage("Microsoft.Naming", "CA1704", MessageId = "Num", Justification = "Named for consistancy with key naming conventions.")]
        NumPad6 = 0x4D,
        [SuppressMessage("Microsoft.Naming", "CA1704", MessageId = "Num", Justification = "Named for consistancy with key naming conventions.")]
        NumPad7 = 0x47,
        [SuppressMessage("Microsoft.Naming", "CA1704", MessageId = "Num", Justification = "Named for consistancy with key naming conventions.")]
        NumPad8 = 0x48,
        [SuppressMessage("Microsoft.Naming", "CA1704", MessageId = "Num", Justification = "Named for consistancy with key naming conventions.")]
        NumPad9 = 0x49,

        [SuppressMessage("Microsoft.Naming", "CA1704", MessageId = "Num", Justification = "Named for consistancy with key naming conventions.")]
        NumPadEnter = 0x9C,
        [SuppressMessage("Microsoft.Naming", "CA1704", MessageId = "Num", Justification = "Named for consistancy with key naming conventions.")]
        NumPadMinus = 0x4A,
        [SuppressMessage("Microsoft.Naming", "CA1704", MessageId = "Num", Justification = "Named for consistancy with key naming conventions.")]
        NumPadPlus = 0x4E,
        [SuppressMessage("Microsoft.Naming", "CA1704", MessageId = "Num", Justification = "Named for consistancy with key naming conventions.")]
        NumPadMultiply = 0x37,
        [SuppressMessage("Microsoft.Naming", "CA1704", MessageId = "Num", Justification = "Named for consistancy with key naming conventions.")]
        NumPadDivide = 0xB5,
        [SuppressMessage("Microsoft.Naming", "CA1704", MessageId = "Num", Justification = "Named for consistancy with key naming conventions.")]
        NumPadPeriod = 0x53,

        Tab = 0x0F,

        Backspace = 0x0E,

        Space = 0x39,

        [SuppressMessage("Microsoft.Naming", "CA1704", MessageId = "A", Justification = "Named for consistancy with key naming conventions.")]
        A = 0x1E,
        [SuppressMessage("Microsoft.Naming", "CA1704", MessageId = "B", Justification = "Named for consistancy with key naming conventions.")]
        B = 0x30,
        [SuppressMessage("Microsoft.Naming", "CA1704", MessageId = "C", Justification = "Named for consistancy with key naming conventions.")]
        C = 0x2E,
        [SuppressMessage("Microsoft.Naming", "CA1704", MessageId = "D", Justification = "Named for consistancy with key naming conventions.")]
        D = 0x20,
        [SuppressMessage("Microsoft.Naming", "CA1704", MessageId = "E", Justification = "Named for consistancy with key naming conventions.")]
        E = 0x12,
        [SuppressMessage("Microsoft.Naming", "CA1704", MessageId = "F", Justification = "Named for consistancy with key naming conventions.")]
        F = 0x21,
        [SuppressMessage("Microsoft.Naming", "CA1704", MessageId = "G", Justification = "Named for consistancy with key naming conventions.")]
        G = 0x22,
        [SuppressMessage("Microsoft.Naming", "CA1704", MessageId = "H", Justification = "Named for consistancy with key naming conventions.")]
        H = 0x23,
        [SuppressMessage("Microsoft.Naming", "CA1704", MessageId = "I", Justification = "Named for consistancy with key naming conventions.")]
        I = 0x17,
        [SuppressMessage("Microsoft.Naming", "CA1704", MessageId = "J", Justification = "Named for consistancy with key naming conventions.")]
        J = 0x24,
        [SuppressMessage("Microsoft.Naming", "CA1704", MessageId = "K", Justification = "Named for consistancy with key naming conventions.")]
        K = 0x25,
        [SuppressMessage("Microsoft.Naming", "CA1704", MessageId = "L", Justification = "Named for consistancy with key naming conventions.")]
        L = 0x26,
        [SuppressMessage("Microsoft.Naming", "CA1704", MessageId = "M", Justification = "Named for consistancy with key naming conventions.")]
        M = 0x32,
        [SuppressMessage("Microsoft.Naming", "CA1704", MessageId = "N", Justification = "Named for consistancy with key naming conventions.")]
        N = 0x31,
        [SuppressMessage("Microsoft.Naming", "CA1704", MessageId = "O", Justification = "Named for consistancy with key naming conventions.")]
        O = 0x18,
        [SuppressMessage("Microsoft.Naming", "CA1704", MessageId = "P", Justification = "Named for consistancy with key naming conventions.")]
        P = 0x19,
        [SuppressMessage("Microsoft.Naming", "CA1704", MessageId = "Q", Justification = "Named for consistancy with key naming conventions.")]
        Q = 0x10,
        [SuppressMessage("Microsoft.Naming", "CA1704", MessageId = "R", Justification = "Named for consistancy with key naming conventions.")]
        R = 0x13,
        [SuppressMessage("Microsoft.Naming", "CA1704", MessageId = "S", Justification = "Named for consistancy with key naming conventions.")]
        S = 0x1F,
        [SuppressMessage("Microsoft.Naming", "CA1704", MessageId = "T", Justification = "Named for consistancy with key naming conventions.")]
        T = 0x14,
        [SuppressMessage("Microsoft.Naming", "CA1704", MessageId = "U", Justification = "Named for consistancy with key naming conventions.")]
        U = 0x16,
        [SuppressMessage("Microsoft.Naming", "CA1704", MessageId = "V", Justification = "Named for consistancy with key naming conventions.")]
        V = 0x2F,
        [SuppressMessage("Microsoft.Naming", "CA1704", MessageId = "W", Justification = "Named for consistancy with key naming conventions.")]
        W = 0x11,
        [SuppressMessage("Microsoft.Naming", "CA1704", MessageId = "X", Justification = "Named for consistancy with key naming conventions.")]
        X = 0x2D,
        [SuppressMessage("Microsoft.Naming", "CA1704", MessageId = "Y", Justification = "Named for consistancy with key naming conventions.")]
        Y = 0x15,
        [SuppressMessage("Microsoft.Naming", "CA1704", MessageId = "Z", Justification = "Named for consistancy with key naming conventions.")]
        Z = 0x2C,

        Grave = 0x29,

        Number1 = 0x02,
        Number2 = 0x03,
        Number3 = 0x04,
        Number4 = 0x05,
        Number5 = 0x06,
        Number6 = 0x07,
        Number7 = 0x08,
        Number8 = 0x09,
        Number9 = 0x0A,
        Number0 = 0x0B,

        Minus = 0x0C,
        Equals = 0x0D,

        LeftBracket = 0x1A,
        RightBracket = 0x1B,
        Backslash = 0x2B,
        Semicolon = 0x27,
        Apostrophe = 0x28,
        Comma = 0x33,
        Period = 0x34,
        Slash = 0x35,

        CapsLock = 0x3A,

        PlayPause = 0xA2,
        Stop = 0xA4,
        NextTrack = 0x99,
        PreviousTrack = 0x90,

        VolumeUp = 0xB0,
        VolumeDown = 0xAE,
        Mute = 0xA0,

        MediaSelect = 0xED,

        Power = 0xDE,
        Sleep = 0xDF,
        Wake = 0xE3,

        WebBack = 0xEA,
        WebForward = 0xE9,
        WebStop = 0xE8,
        WebRefresh = 0xE7,
        WebHome = 0xB2,
        WebSearch = 0xE5,
        WebBookmarks = 0xE6,

        Mail = 0xEC,

        MyComputer = 0xEB,

        Calculator = 0xA1,

        Yen = 0x7D,
        Kana = 0x70,
        Kanji = 0x94,
        Convert = 0x79,
        NoConvert = 0x7B,
        Circumflex = 0x90,
    }
}
