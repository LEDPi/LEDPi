namespace LED_PI_GMTest
{
    internal interface IModule
    {
        void Draw(ref Color[,] image);
        object GetSettings();
        string Name { get; }
    }
}
