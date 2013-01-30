namespace Windower
{
    using System;
    using System.Globalization;
    using System.IO;
    using System.Reflection;
    using System.Runtime.ConstrainedExecution;
    using System.Runtime.InteropServices;
    using System.Security;
    using System.Security.Permissions;
    using System.Diagnostics;

    [SecurityPermission(SecurityAction.LinkDemand, Flags = SecurityPermissionFlag.UnmanagedCode)]
    internal static class NativeMethods
    {
        private static readonly object sync = new object();
        private static bool initialized = false;

        internal static void Initialize()
        {
            lock (sync)
            {
                if (!initialized)
                {
                    Assembly assembly = typeof(NativeMethods).Assembly;
                    string path = Path.Combine(Path.GetTempPath(), String.Format(CultureInfo.InvariantCulture, "windowerhelper.{0}", assembly.GetName().Version));
                    path = Path.Combine(path, IntPtr.Size == 4 ? "x86" : "x64");
                    Directory.CreateDirectory(path);
                    path = Path.Combine(path, "windowerhelper.dll");
                    Console.WriteLine(path);

                    Stream o = null;
                    try
                    {
                        try
                        {
                            o = File.Open(path, FileMode.Create, FileAccess.Write);
                        }
                        catch (IOException e)
                        {
                            Trace.TraceError(e.ToString());
                        }

                        if (o != null)
                        {
                            string name = IntPtr.Size == 4 ? "Windower.res.x86.windowerhelper.dll" : "Windower.res.x64.windowerhelper.dll";

                            using (Stream i = assembly.GetManifestResourceStream(name))
                            {
                                int count;
                                byte[] buffer = new byte[8192];
                                while ((count = i.Read(buffer, 0, buffer.Length)) != 0)
                                {
                                    o.Write(buffer, 0, count);
                                }
                            }

                            o.Flush();
                        }
                    }
                    catch (Exception e)
                    {
                        Trace.TraceError(e.ToString());
                        throw;
                    }
                    finally
                    {
                        if (o != null)
                        {
                            o.Dispose();
                        }
                    }

                    LoadLibrary(path);

                    initialized = true;
                }
            }
        }

        [DllImport("windowerhelper.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern ErrorCode windower_create(out SafeInstanceHandle result, uint process);

        [DllImport("windowerhelper.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern ErrorCode windower_create_remote(out SafeInstanceHandle result, byte[] domain, uint process);

        [SuppressUnmanagedCodeSecurity]
        [ReliabilityContract(Consistency.WillNotCorruptState, Cer.Success)]
        [DllImport("windowerhelper.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern ErrorCode windower_delete(IntPtr handle);

        [DllImport("windowerhelper.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern ErrorCode windower_get_version(SafeInstanceHandle handle, out uint result);

        [DllImport("windowerhelper.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern ErrorCode windower_send_string(SafeInstanceHandle handle, byte[] text);

        [DllImport("windowerhelper.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern ErrorCode windower_set_key_state(SafeInstanceHandle handle, Key key, KeyState state);

        [DllImport("windowerhelper.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern ErrorCode windower_block(SafeInstanceHandle handle, InputKinds input_kind);

        [DllImport("windowerhelper.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern ErrorCode windower_unblock(SafeInstanceHandle handle, InputKinds input_kind);

        [DllImport("windowerhelper.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern ErrorCode windower_next_command(SafeInstanceHandle handle, out SafeCommandHandle result);

        [SuppressUnmanagedCodeSecurity]
        [ReliabilityContract(Consistency.WillNotCorruptState, Cer.Success)]
        [DllImport("windowerhelper.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern ErrorCode windower_command_delete(IntPtr handle);

        [DllImport("windowerhelper.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern ErrorCode windower_command_length(SafeCommandHandle handle, out uint result);

        [DllImport("windowerhelper.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern ErrorCode windower_command_string(SafeCommandHandle handle, out IntPtr result);

        [DllImport("windowerhelper.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern ErrorCode windower_text_create(SafeInstanceHandle handle, out SafeTextHandle result, byte[] name);

        [SuppressUnmanagedCodeSecurity]
        [ReliabilityContract(Consistency.WillNotCorruptState, Cer.Success)]
        [DllImport("windowerhelper.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern ErrorCode windower_text_delete(IntPtr text_handle);

        [DllImport("windowerhelper.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern ErrorCode windower_text_set_text(SafeTextHandle text_handle, byte[] text);

        [DllImport("windowerhelper.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern ErrorCode windower_text_show(SafeTextHandle text_handle);

        [DllImport("windowerhelper.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern ErrorCode windower_text_hide(SafeTextHandle text_handle);

        [DllImport("windowerhelper.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern ErrorCode windower_text_set_location(SafeTextHandle text_handle, int x, int y);

        [DllImport("windowerhelper.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern ErrorCode windower_text_set_foreground(SafeTextHandle text_handle, byte r, byte g, byte b, byte a);

        [DllImport("windowerhelper.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern ErrorCode windower_text_set_background(SafeTextHandle text_handle, byte r, byte g, byte b, byte a);

        [DllImport("windowerhelper.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern ErrorCode windower_text_show_background(SafeTextHandle text_handle);

        [DllImport("windowerhelper.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern ErrorCode windower_text_hide_background(SafeTextHandle text_handle);

        [DllImport("windowerhelper.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern ErrorCode windower_text_set_font(SafeTextHandle text_handle, byte[] typeface, float size);

        [DllImport("windowerhelper.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern ErrorCode windower_text_set_weight(SafeTextHandle text_handle, FontWeight weight);

        [DllImport("windowerhelper.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern ErrorCode windower_text_set_style(SafeTextHandle text_handle, FontStyles style);

        [DllImport("windowerhelper.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern ErrorCode windower_text_set_alignment(SafeTextHandle text_handle, TextAlignment alignment);

        [DllImport("windowerhelper.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern ErrorCode windower_text_set_padding(SafeTextHandle text_handle, float pixels);

        [DllImport("Kernel32.dll", CallingConvention = CallingConvention.Winapi, SetLastError = true, CharSet = CharSet.Unicode)]
        private static extern IntPtr LoadLibrary(string lpFileName);
    }
}
