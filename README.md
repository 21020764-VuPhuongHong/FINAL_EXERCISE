# FINAL_EXERCISE 
(BÀI TẬP LỚN CUỐI KHÓA LẬP TRÌNH NÂNG CAO - INT2215 1)
  * Họ và tên: Vũ Phượng Hồng 
  * MSV: 21020764
# Game Super Mario Bros (sử dụng thư viện SDL2)
## 1. Hướng dẫn cài đặt: cách lấy chương trình về và các câu lệnh, cài đặt để có thể chạy được chương trình
  * Download MinGW-W64 compilers qua địa chỉ: https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/8.1.0/threads-posix/seh/x86_64-8.1.0-release-posix-seh-rt_v6-rev0.7z/download (cần download chính xác bản này)
  * Cài đặt đường dẫn PATH đến <ROOTDIR>\mingw64\bin (VD: C:\x86_64-8.1.0-release-posix-seh-rt_v6-rev0\mingw64\bin)
  * Clone repo về qua câu lệnh: git clone https://github.com/21020764-VuPhuongHong/FINAL_EXERCISE.git
  * Trong Command Prompt, thay đổi đường dẫn đến thư mục Mario_Project trong thư mục FINAL_EXERCISE (<ROOTDIR>\FINAL_EXERCISE\Mario_Project)
  * Chạy chương trình bằng câu lệnh mingw32-make hoặc gõ trực tiếp lệnh: g++ -Iinclude -Llib source/*.cpp -o MarioGame -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer
  * Sau khi biên dịch thành công, gõ lệnh MarioGame.exe (hoặc .\MarioGame.exe) để chạy game
## 2. Mô tả chung về trò chơi, các ý tưởng chính
  ![image](https://user-images.githubusercontent.com/100524815/170909206-50be876a-7324-43b6-bb2d-e85ba38ff7e8.png)
  ![image](https://user-images.githubusercontent.com/100524815/170909372-324abffe-0c6e-4489-a4fe-03099b0454d3.png)
  ![image](https://user-images.githubusercontent.com/100524815/170909471-395a7ad2-b951-4dbd-90ce-85fb58a4f7a5.png)
  ![image](https://user-images.githubusercontent.com/100524815/170909562-eb65f6cc-1554-41e6-8db0-42ea380471f0.png)
### Mô tả chung:
  * Kế thừa game Super Mario Bros cổ điển, trong phiên bản game này, người chơi sẽ nhập vai Mario vượt qua chặng đường đầy vực sâu, các chướng ngại vật và các sinh vật tấn công để giải cứu công chúa. 
  * **Cách chơi:** Sử dụng các phím mũi tên [↑→↓←] để điều khiển Mario di chuyển, nhấn phím Spacebar để bắn ra quả cầu lửa khi ở chế độ Fire Mario.
 ### Các ý tưởng chính: 
  * Menu: cài đặt kích thước và vị trí cố định của các nút bấm, quản lý các tương tác giữa chuột với các nút bấm đó, tùy vào loại tương tác (di chuột vào khu vực nút, click chuột, nhả chuột...) mà quyết định các đối tượng sẽ được hiển thị tiếp theo và thiết lập chế độ game để bắt đầu chơi.
  * Trong game:
    * Căn chỉnh tọa độ, sắp xếp sao cho khi hiển thị ảnh của các đối tượng riêng lẻ khớp lại với nhau tạo thành bối cảnh game.
    * Trong quá trình chơi, quản lý input từ bàn phím qua chức năng của thư viện SDL2, tùy vào phím mũi tên [→↑←] được nhấn mà thay đổi tọa độ hiển thị và hình ảnh các tư thế của Mario một cách thích hợp để tạo hiệu ứng đang chạy/ nhảy, nếu phím [↓] được nhấn khi Mario đang ở đúng vị trí phía trên đường ống thì thay đổi bối cảnh xuống đường hầm, nếu phím Spacebar được nhấn khi Mario đang ở trạng thái Fire Mario thì hiển thị quả cầu lửa bắn ra theo chiều ngang, hiệu ứng cháy nổ và kẻ thù bị tiêu diệt.
    * Kiểm tra va chạm giữa các đối tượng trong game:
      * Giữa Mario với các sinh vật tấn công, các chướng ngại vật là khối cứng không thể phá vỡ, các viên gạch có thể phá vỡ, các đồng xu, các vật phẩm đặc biệt và với cột cờ ở cuối mỗi màn... --> Xác định loại va chạm để trừ mạng, hiển thị hiệu ứng "dying", bắt đầu lại màn chơi hoặc cộng điểm, cộng xu, cộng mạng, thay đổi sang chế độ Super/ Fire/ Immortal Mario hoặc chuyển sang level tiếp theo...
      * Giữa các sinh vật tấn công với quả cầu lửa của Mario, giữa các loại sinh vật tấn công với nhau, giữa sinh vật tấn công với khối gạch mà chúng đứng trên...
      * Giữa vật phẩm đặc biệt với khối gạch mà chúng đứng trên... <br>
      --> Tùy loại va chạm mà hiển thị các hiệu ứng.
 ## 3. Các chức năng đã cài đặt <br> 
  > Link video minh họa: https://youtu.be/IWLjU9hzgAg
  * Menu của game gồm 4 nút bấm: 
    * **PLAY**: Bắt đầu chơi
    * **OPTIONS**: Mở ra Submenu để người chơi lựa chọn tốc độ game (mức độ nhanh dần từ 1 đến 9), chế độ chơi (CLASSIC WORLD/ CUSTOM WORLD) và bối cảnh của CUSTOM WORLD (WINTER WORLD/ SUMMER WORLD)
    * **HELP**: Hướng dẫn cách chơi
    * **EXIT**: Thoát game
  * Game có 2 chế độ để người chơi lựa chọn: Classic World và Custom World: <br>
  **Chế độ Classic World gồm 4 level từ 1 đến 4**
  ![image](https://user-images.githubusercontent.com/100524815/170910561-9f2af373-88bf-4068-a934-d167836619f3.png) <br>
  **Chế độ Custom World có 2 bối cảnh để người chơi lựa chọn là: Winter World và Summer World**
  ![image](https://user-images.githubusercontent.com/100524815/170910598-12c10a48-9e43-4486-b762-d461841340be.png)
  ![image](https://user-images.githubusercontent.com/100524815/170910632-bbbe2fd2-3dc0-4826-9a64-965b01c4f6ec.png) <br> 
  Mario cần đến được cột cờ ở cuối mỗi màn chơi để chiến thắng màn chơi đó. Khi bắt đầu chơi, Mario sẽ có 3 mạng, mỗi lần chạm phải sinh vật tấn công hoặc rơi xuống vực sẽ mất 1 mạng và phải chơi lại từ đầu của level.
  * Trên đường tới lâu đài của công chúa, Mario sẽ cố gắng tiêu diệt các sinh vật tấn công  ![creature1](https://user-images.githubusercontent.com/100524815/170977679-926569e3-b4f8-4e7d-b1b7-68e9fd03e1a5.png) ![creature6](https://user-images.githubusercontent.com/100524815/170977797-03d400ed-6a84-47e0-a450-f1f82a57daf0.png) ![red_turtle1](https://user-images.githubusercontent.com/100524815/170977860-8d8cd36e-af3d-4b54-91ff-64e8fb96b8bc.png) ![turtle1](https://user-images.githubusercontent.com/100524815/170977937-abe35d78-8c7d-46f2-9636-3e3520d0353e.png) bằng cách nhảy lên đầu chúng để được cộng điểm (tuy nhiên một số loại sinh vật như  ![plant2](https://user-images.githubusercontent.com/100524815/170978748-a79091e2-bae8-4c1d-8793-45b970d07452.png) ![plant4](https://user-images.githubusercontent.com/100524815/170978803-4cd64972-796f-4c1b-9157-2b0369a29ed3.png) ![bombardier_right](https://user-images.githubusercontent.com/100524815/170978824-251cf84f-e430-46e7-a28c-cf5322ed643d.png) không thể bị tiêu diệt bằng cách đó), cố gắng thu thập thật nhiều đồng xu nằm rải rác trên đường và nhảy lên đánh vào các viên gạch  ![block4](https://user-images.githubusercontent.com/100524815/170979225-733b50a1-ce63-497c-82b5-bec7f69fc2c0.png) (nhất là những viên gạch có dấu chấm hỏi  ![block10](https://user-images.githubusercontent.com/100524815/170979300-86ebef61-8ec9-4301-8b51-02ac6eaecfe6.png)) để thu thập đồng xu hoặc vật phẩm đặc biệt giấu trong chúng. 
 * Có 3 loại vật phẩm đặc biệt là:
    * ***Super Mushroom***  ![mushroom_red](https://user-images.githubusercontent.com/100524815/170914186-d971017a-8a43-4ce5-90e4-71e3a580f3af.png) ![mushroom_green](https://user-images.githubusercontent.com/100524815/170914253-8cad14cb-1ea7-4551-afe1-8dc900d5d010.png)  ![mushroom_purple](https://user-images.githubusercontent.com/100524815/170914282-08824216-a5b1-4c56-b9fe-0b3d9278ccbc.png) : Khi ăn được Super Mushroom, tùy vào loại nấm mà Mario có thể được cộng thêm 1 mạng hoặc trở thành Super Mario  ![mario_right6](https://user-images.githubusercontent.com/100524815/170979742-ddf2b973-13c2-4fe4-b164-395b22d2e2a7.png) - lớn gấp đôi kích thước ban đầu và có khả năng phá vỡ những viên gạch ở phía trên anh ấy. Khi bị sinh vật tấn công đụng trúng trong trạng thái Super Mario, Mario sẽ trở về kích thước bình thường chứ không chết.
    * ***Fire Flower***  ![flower1](https://user-images.githubusercontent.com/100524815/170915117-27378afc-d2bb-4cc1-b11e-e96ee448aa89.png) : Khi ăn được Fire Flower, Mario sẽ chuyển thành Fire Mario  ![mario_right26](https://user-images.githubusercontent.com/100524815/170979799-ff6df352-23a3-4214-aba4-ff5e7ff3d4b8.png) - có khả năng bắn ra các quả cầu lửa để tiêu diệt kẻ thù. Khi bị sinh vật tấn công đụng trúng trong trạng thái này, Mario cũng sẽ trở về kích thước bình thường chứ không chết.
    * ***Super Star***  ![star3](https://user-images.githubusercontent.com/100524815/170915565-0eb29523-7d02-40a9-9451-6289489b6efa.png) : Khi ăn được Super Star, Mario sẽ chuyển sang trạng thái Immortal (bất tử) và dễ dàng tiêu diệt kẻ thù bằng cách đơn giản là chạm vào chúng, tuy nhiên trạng thái này chỉ là tạm thời và sẽ hết tác dụng sau một thời gian ngắn. 
  
 







  
 
 
