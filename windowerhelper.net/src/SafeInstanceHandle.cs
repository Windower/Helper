﻿namespace Windower
{
    using System;
    using System.Runtime.ConstrainedExecution;
    using System.Runtime.InteropServices;

    internal sealed class SafeInstanceHandle : SafeHandle
    {
        private SafeInstanceHandle()
            : base(IntPtr.Zero, true)
        {
        }

        public override bool IsInvalid
        {
            [ReliabilityContract(Consistency.WillNotCorruptState, Cer.Success)]
            [PrePrepareMethod]
            get
            {
                return this.handle == IntPtr.Zero;
            }
        }

        [ReliabilityContract(Consistency.WillNotCorruptState, Cer.Success)]
        [PrePrepareMethod]
        protected override bool ReleaseHandle()
        {
            return NativeMethods.windower_delete(this.handle) == 0;
        }
    }
}
