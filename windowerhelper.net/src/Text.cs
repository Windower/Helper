namespace Windower
{
    using System;
    using System.Diagnostics.CodeAnalysis;
    using System.Text;

    [SuppressMessage("Microsoft.Naming", "CA1724", Justification = "Named for consistancy with C, C++, and Java bindings.")]
    public sealed class Text : IDisposable
    {
        private bool disposed = false;
        private SafeTextHandle handle;

        public Text(Instance instance, string name)
        {
            int asciinamelength = Instance.ASCII.GetMaxByteCount(name.Length) + 1;
            byte[] asciiname = new byte[asciinamelength];
            Instance.ASCII.GetBytes(name, 0, name.Length, asciiname, 0);
            WindowerException.Check(NativeMethods.windower_text_create(instance.Handle, out this.handle, asciiname));
        }

        public void Dispose()
        {
            if (!this.disposed)
            {
                this.handle.Dispose();
                this.disposed = true;
            }
        }

        public void SetText(string text)
        {
            if (text == null)
            {
                throw new ArgumentNullException("text");
            }

            int utf8textlength = Instance.UTF8.GetMaxByteCount(text.Length) + 1;
            byte[] utf8text = new byte[utf8textlength];
            Instance.UTF8.GetBytes(text, 0, text.Length, utf8text, 0);
            WindowerException.Check(NativeMethods.windower_text_set_text(this.handle, utf8text));
        }

        public void Show()
        {
            WindowerException.Check(NativeMethods.windower_text_show(this.handle));
        }

        public void Hide()
        {
            WindowerException.Check(NativeMethods.windower_text_hide(this.handle));
        }

        public void SetLocation(int x, int y)
        {
            WindowerException.Check(NativeMethods.windower_text_set_location(this.handle, x, y));
        }

        public void SetForeground(byte red, byte green, byte blue)
        {
            WindowerException.Check(NativeMethods.windower_text_set_foreground(this.handle, red, green, blue, 255));
        }

        public void SetForeground(byte red, byte green, byte blue, byte alpha)
        {
            WindowerException.Check(NativeMethods.windower_text_set_foreground(this.handle, red, green, blue, alpha));
        }

        public void SetBackground(byte red, byte green, byte blue)
        {
            WindowerException.Check(NativeMethods.windower_text_set_background(this.handle, red, green, blue, 255));
        }

        public void SetBackground(byte red, byte green, byte blue, byte alpha)
        {
            WindowerException.Check(NativeMethods.windower_text_set_background(this.handle, red, green, blue, alpha));
        }

        public void ShowBackground()
        {
            WindowerException.Check(NativeMethods.windower_text_show_background(this.handle));
        }

        public void HideBackground()
        {
            WindowerException.Check(NativeMethods.windower_text_hide_background(this.handle));
        }

        public void SetFont(string typeface, float size)
        {
            if (typeface == null)
            {
                throw new ArgumentNullException("typeface");
            }

            int utf8typefacelength = Instance.UTF8.GetMaxByteCount(typeface.Length) + 1;
            byte[] utf8typeface = new byte[utf8typefacelength];
            Instance.UTF8.GetBytes(typeface, 0, typeface.Length, utf8typeface, 0);
            WindowerException.Check(NativeMethods.windower_text_set_font(this.handle, utf8typeface, size));
        }
        
        public void SetWeight(FontWeight weight)
        {
            WindowerException.Check(NativeMethods.windower_text_set_weight(this.handle, weight));
        }

        public void SetStyle(FontStyles style)
        {
            WindowerException.Check(NativeMethods.windower_text_set_style(this.handle, style));
        }

        public void SetAlignment(TextAlignment alignment)
        {
            WindowerException.Check(NativeMethods.windower_text_set_alignment(this.handle, alignment));
        }

        public void SetPadding(float pixels)
        {
            if (pixels < 0)
            {
                throw new ArgumentOutOfRangeException("pixels");
            }

            WindowerException.Check(NativeMethods.windower_text_set_padding(this.handle, pixels));
        }
    }
}
