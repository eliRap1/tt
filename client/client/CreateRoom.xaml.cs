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
    /// Interaction logic for CreateRoom.xaml
    /// </summary>
    public partial class CreateRoom : Page
    {
        public CreateRoom()
        {
            InitializeComponent();
        }

        private void CreateRoom_Click(object sender, RoutedEventArgs e)
        {
            byte[] request = Serializer.SearalizeCreateRoomRequest(int.Parse(PlayersAmountTextBox.Text), int.Parse(QuestionTimeTextBox.Text), RoomNameTextBox.Text, int.Parse(QuestionAmount.Text));
            byte[] response = MainWindow.communicator.sendAndReceive(request);
            int status = Deserializer.extractStatus(response);
 
            if (status == 1)
            {
                MessageBox.Show("Room created successfully!");
                request = Serializer.serializeGetRoomsRequest();
                response = MainWindow.communicator.sendAndReceive(request);
                int id = -1;
                List<RoomInfo> rooms = Deserializer.DeserializeGetRoomsResponse(response);
                Room roomNow;
                foreach (var room in rooms)
                {
                    if (room.name == RoomNameTextBox.Text)
                    {
                        id = room.id;
                        roomNow = new Room(room);
                        request = Serializer.SearalizeJoinRoomRequest(id);
                        response = MainWindow.communicator.sendAndReceive(request);
                        if(Deserializer.extractStatus(response) != 1) MessageBox.Show("Error joining room");
                        JoinRoomFrame.Navigate(roomNow);
                    }
                }
            }
        }

        private void Back_Click(object sender, RoutedEventArgs e)
        {
            JoinRoomFrame.Navigate(new Trivia());
        }
    }
}
