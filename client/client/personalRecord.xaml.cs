using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace client
{
    /// <summary>
    /// Interaction logic for personalRecord.xaml
    /// </summary>
    public partial class personalRecord : Page
    {
        private const int PERSONAL_RECORD_NUMBER = 10;
        public personalRecord()
        {
            InitializeComponent();
            LoadPersonalStats();
        }

        private void LoadPersonalStats()
        {
            try
            {
                byte[] request = Serializer.SerializeSimpleRequest(PERSONAL_RECORD_NUMBER); 
                byte[] response = MainWindow.communicator.sendAndReceive(request);

                const int headerSize = 5;
                if (response.Length <= headerSize)
                    throw new Exception("Response too short");

                string json = Encoding.UTF8.GetString(response, headerSize, response.Length - headerSize);

                int start = json.IndexOf("\"statistics\":[");
                if (start == -1)
                    throw new Exception("Missing statistics");

                start += "\"statistics\":[".Length;
                int end = json.IndexOf("]", start);
                string raw = json.Substring(start, end - start);
                string[] items = raw.Split(new[] { "\",\"" }, StringSplitOptions.RemoveEmptyEntries);

                foreach (string stat in items)
                {
                    string clean = stat.Replace("\"", "").Trim();
                    AddStatCard(clean);
                }
            }
            catch (Exception ex)
            {
                AddStatCard($"error: {ex.Message}");
            }
        }

        private void AddStatCard(string text)
        {
            Border card = new Border
            {
                Background = new SolidColorBrush(Color.FromRgb(245, 245, 245)), 
                CornerRadius = new CornerRadius(16),
                Margin = new Thickness(0, 0, 0, 20),
                Padding = new Thickness(20),
                Width = 600,
                HorizontalAlignment = HorizontalAlignment.Center,
                Effect = new System.Windows.Media.Effects.DropShadowEffect
                {
                    Color = Colors.Black,
                    BlurRadius = 10,
                    ShadowDepth = 3,
                    Opacity = 0.3
                }
            };

            TextBlock block = new TextBlock
            {
                Text = text,
                FontSize = 18,
                Foreground = Brushes.Black,
                FontWeight = FontWeights.Medium,
                TextWrapping = TextWrapping.Wrap,
                TextAlignment = TextAlignment.Center
            };

            card.Child = block;
            StatsPanel.Children.Add(card);
        }
    }
}
