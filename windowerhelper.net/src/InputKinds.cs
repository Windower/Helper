namespace Windower
{
    using System;

    [Flags]
    public enum InputKinds
    {
        Keyboard = 1,
        Mouse = 2,

        All = Keyboard | Mouse,
    }
}
