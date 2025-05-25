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
    /// Interaction logic for recordGrid.xaml
    /// </summary>
    public partial class recordGrid : Page
    {
        private const int ALL_PLAYERS = 9;
        public recordGrid()
        {
            InitializeComponent();
            LoadHighScores();
        }

        private void LoadHighScores()
        {
            try
            {
                byte[] request = Serializer.SerializeSimpleRequest(ALL_PLAYERS); // HIGH_SCORE_CODE
                byte[] response = MainWindow.communicator.sendAndReceive(request);

                const int headerSize = 5;
                if (response.Length <= headerSize)
                    throw new Exception("Response too short");

                string json = Encoding.UTF8.GetString(response, headerSize, response.Length - headerSize);

                int start = json.IndexOf("\"highScores\":[");
                if (start == -1)
                    throw new Exception("Missing highScores");

                start += "\"highScores\":[".Length;
                int end = json.IndexOf("]", start);
                string raw = json.Substring(start, end - start);
                string[] items = raw.Split(new[] { "\",\"" }, StringSplitOptions.RemoveEmptyEntries);

                foreach (string score in items)
                {
                    string clean = score.Replace("\"", "").Trim();
                    AddScoreCard(clean);
                }
            }
            catch (Exception ex)
            {
                AddScoreCard($"error: {ex.Message}");
            }
        }

        private void AddScoreCard(string text)
        {
            Border card = new Border
            {
                Background = Brushes.White,
                CornerRadius = new CornerRadius(12),
                Margin = new Thickness(0, 0, 0, 15),
                Padding = new Thickness(16),
                Width = 600,
                HorizontalAlignment = HorizontalAlignment.Center
            };

            TextBlock block = new TextBlock
            {
                Text = text,
                FontSize = 16,
                Foreground = Brushes.Black,
                FontWeight = FontWeights.Bold
            };

            card.Child = block;
            HighScoresPanel.Children.Add(card); 
        }

        private void BackButton_Click(object sender, RoutedEventArgs e)
        {
            statisticsFrame.Navigate(new Statistics());
        }
    }
}
