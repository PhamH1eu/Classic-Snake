# Classic-Snake
Phạm Minh Hiếu 21020319
1. Cách cài đặt
  -Tạo thư mục muốn cài đặt game, mở bằng Visual Studio Code, nhập vào terminal
  -git clone https://github.com/PhamH1eu/Classic-Snake.git
  -cd Classic-Snake
  -mingw32-make -f Makefile
  -./main.exe
  
2. Game rắn ăn táo cơ bản
  - Khởi đầu với đầu rắn, rắn sẽ dài thêm 1 đốt khi ăn được táo sinh ngẫu nhiên trên sân
  - Game thua khi rắn tự đâm chính mình hoặc đâm vào tường
  - Điều khiển bằng w a s d để lên xuống trái phải
3. Tính năng
  - Ban đầu là tổ rắn, bấm w a s d để rắn di chuyển ra khỏi tổ.
  ![image](https://user-images.githubusercontent.com/100515892/169095975-1100551e-ed72-4d62-9cfc-e85343db9e73.png)
  - Có đầy đủ hình ảnh đầu đuôi thân rắn khi chuyển hướng.
  ![image](https://user-images.githubusercontent.com/100515892/169096537-3ef91188-fafc-4e70-90ba-0a93576f9b0f.png)
  - Khi kết thúc game sẽ hiện số điểm người chơi đã đạt được.
  ![image](https://user-images.githubusercontent.com/100515892/169096318-0328d6d9-7063-4682-9bd5-9f3eb78b4cc4.png)
  - Có âm thanh nền, âm thanh khi rắn ăn quả táo và chạm tường.
  - link demo: https://youtu.be/7Su_WdWWJr0
4. Các kỹ thuật đã sử dụng
  - Đồ họa, render text, âm thanh với SDL2
  - Vector
  - Struct
  - ...
5. Kết luận
  - Đã rút ra được một số kiến thức về lập trình hướng đối tượng, cách sử dụng thư viện đồ họa để tạo nên 1 game cơ bản
  - Hướng phát triển: Làm thêm menu, tạo ra các level cho người chơi chọn, mỗi level là 1 map khác nhau với chướng ngại vật khác nhau
