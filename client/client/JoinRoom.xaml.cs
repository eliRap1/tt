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
    /// Interaction logic for JoinRoom.xaml
    /// </summary>
    public partial class JoinRoom : Page
    {
        public JoinRoom()
        {
            InitializeComponent();
            byte[] request = Serializer.serializeGetRoomsRequest();
            byte[] response = MainWindow.communicator.sendAndReceive(request);

            List<Room> rooms = Deserializer.DeserializeGetRoomsResponse(response);

            foreach (var room in rooms)
            {
                AddRoomCard(room.name, room.maxPlayers);
            }

        }
        private void AddRoomCard(string roomName, int maxPlayers)
        {
            // create card container
            Border roomCard = new Border
            {
                Background = Brushes.White,
                CornerRadius = new CornerRadius(12),
                Margin = new Thickness(0, 0, 0, 15),
                Padding = new Thickness(16),
                Width = 700,
                HorizontalAlignment = HorizontalAlignment.Center,
            };

            DockPanel dock = new DockPanel();

            // left side text
            StackPanel textPanel = new StackPanel();
            TextBlock nameText = new TextBlock
            {
                Text = $"Room Name: {roomName}",
                FontSize = 20,
                FontWeight = FontWeights.Bold,
                Foreground = Brushes.Navy
            };
            TextBlock playersText = new TextBlock
            {
                Text = $"Max Players: {maxPlayers} / {maxPlayers}",
                FontSize = 14,
                Foreground = Brushes.Gray
            };

            textPanel.Children.Add(nameText);
            textPanel.Children.Add(playersText);
            DockPanel.SetDock(textPanel, Dock.Left);

            // right side join 
            Button joinButton = new Button
            {
                Content = "Join",
                Width = 80,
                Height = 30,
                Background = Brushes.DeepSkyBlue,
                Foreground = Brushes.White,
                FontWeight = FontWeights.Bold,
                BorderThickness = new Thickness(0),
                Cursor = Cursors.Hand,
                Margin = new Thickness(10, 0, 0, 0)
            };
            joinButton.Click += (sender, eventArgs) =>
            {
                MessageBox.Show($"Joining room: {roomName}");
                // TODO: Add join logic
            };
            DockPanel.SetDock(joinButton, Dock.Right);

            dock.Children.Add(textPanel);
            dock.Children.Add(joinButton);
            roomCard.Child = dock;

            RoomsPanel.Children.Add(roomCard);
        }

        private void BackButton_Click(object sender, RoutedEventArgs e)
        {
            JoinRoomFrame.Navigate(new Trivia());
        }
    }
}
