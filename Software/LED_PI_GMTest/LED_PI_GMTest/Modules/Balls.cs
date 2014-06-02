using System;

namespace LED_PI_GMTest.Modules
{
    class Balls : IModule
    {
        private class SimpleBall
        {
            public double X;
            public double Y;
            public double dX;
            public double dY;

            public double[] valX = new double[30];
            public double[] valY = new double[30];
        }

        private SimpleBall[] _balls = new SimpleBall[0];
        private readonly Random _rnd = new Random();

        public Balls()
        {
            NumberOfBalls = 3;
            Speed = 1.2;
            BallSize = 8;

            Red = 1;
            Blue = 0.7;
            Green = 0.2;
            RandomSpeed = 4;
            Glow = 0.8;
        }

        public void Draw(ref Color[,] image)
        {
            // _step += Step;

            if (_balls.Length != NumberOfBalls) { Generate(); }

            if (Random)
            {
                if (_rnd.Next(1, 5) == 1)
                {
                    Red += _rnd.Next(-1, 2) * (_rnd.NextDouble() / RandomSpeed);
                    if (Red < 0) Red = 0;
                    if (Red > 1) Red = 1;
                }

                if (_rnd.Next(1, 5) == 1)
                {
                    Green += _rnd.Next(-1, 2) * (_rnd.NextDouble() / RandomSpeed);
                    if (Green < 0) Green = 0;
                    if (Green > 1) Green = 1;
                }

                if (_rnd.Next(1, 5) == 1)
                {
                    Blue += _rnd.Next(-1, 2) * (_rnd.NextDouble() / RandomSpeed);
                    if (Blue < 0) Blue = 0;
                    if (Blue > 1) Blue = 1;
                }
            }

            foreach (var ball in _balls)
            {
                ball.X += (ball.dX * Speed);
                ball.Y += (ball.dY * Speed);

                if (ball.X < 0 || ball.X > 29)
                    ball.dX = -ball.dX;
                if (ball.Y < 0 || ball.Y > 29)
                    ball.dY = -ball.dY;

                for (int x = 0; x < 30; ++x)
                    ball.valX[x] = Glow * ((ball.X - x) * (ball.X - x));

                for (int y = 0; y < 30; ++y)
                    ball.valY[y] = Glow * ((ball.Y - y) * (ball.Y - y));
            }

            for (int x = 0; x < image.GetLength(0); x++)
            {
                for (int y = 0; y < image.GetLength(1); y++)
                {
                    double red = 0, green = 0, blue = 0;

                    foreach (var ball in _balls)
                    {
                        double distance = ball.valX[x] + ball.valY[y];

                        red += BallSize / distance * Red;
                        green += BallSize / distance * Green;
                        blue += BallSize / distance * Blue;
                    }

                    // if (red > 1) red = 1;
                    // if (green > 1) green = 1;
                    // if (blue > 1) blue = 1;

                    var color = new Color(red, green, blue);

                    if (Invert)
                        image[x, y] = color.Invert();
                    else
                        image[x, y] = color;
                }
            }
        }

        private void Generate()
        {
            
            _balls = new SimpleBall[NumberOfBalls];
            for (int i = 0; i < NumberOfBalls; ++i)
            {
                _balls[i] = new SimpleBall
                    {
                        X = _rnd.Next(0, 29),
                        Y = _rnd.Next(0, 29),
                        dX = _rnd.NextDouble() + 0.5,
                        dY = _rnd.NextDouble() + 0.5
                    };

                if (_rnd.Next(1, 3) == 1)
                    _balls[i].dX = -_balls[i].dX;

                if (_rnd.Next(1, 3) == 1)
                    _balls[i].dY = -_balls[i].dY;
            }
        }

        public bool Invert { get; set; }
        public uint NumberOfBalls { set; get; }
        public double Speed { set; get; }
        public double BallSize { set; get; }
        public double Red { set; get; }
        public double Green { set; get; }
        public double Blue { set; get; }
        public bool Random { set; get; }
        public double RandomSpeed { set; get; }
        public double Glow { set; get; }

        public object GetSettings()
        {
            return this;
        }

        public string Name { get { return "Balls";  } }
    }
}
