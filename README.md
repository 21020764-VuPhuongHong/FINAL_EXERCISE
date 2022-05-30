# FINAL_EXERCISE 
(BÀI TẬP LỚN CUỐI KHÓA LẬP TRÌNH NÂNG CAO - INT2215 1)
  * Họ và tên: Vũ Phượng Hồng 
  * MSV: 21020764
## Game Super Mario Bros
### 1. Hướng dẫn cài đặt: cách lấy chương trình về và các câu lệnh, cài đặt để có thể chạy được chương trình
  * Download MinGW-W64 compilers qua địa chỉ: https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/8.1.0/threads-posix/seh/x86_64-8.1.0-release-posix-seh-rt_v6-rev0.7z/download (cần download chính xác bản này)
  * Cài đặt đường dẫn PATH đến <ROOTDIR>\mingw64\bin (VD: C:\x86_64-8.1.0-release-posix-seh-rt_v6-rev0\mingw64\bin)
  * Clone repo về qua câu lệnh: git clone https://github.com/21020764-VuPhuongHong/FINAL_EXERCISE.git
  * Trong Command Prompt, thay đổi đường dẫn đến thư mục Mario_Project trong thư mục FINAL_EXERCISE (<ROOTDIR>\FINAL_EXERCISE\Mario_Project)
  * Chạy chương trình bằng câu lệnh mingw32-make hoặc gõ trực tiếp lệnh: g++ -Iinclude -Llib source/*.cpp -o MarioGame -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer
  * Sau khi biên dịch thành công, gõ lệnh MarioGame.exe (hoặc .\MarioGame.exe) để chạy game
### 2. Mô tả chung về trò chơi, các ý tưởng chính
  ![image](https://user-images.githubusercontent.com/100524815/170909206-50be876a-7324-43b6-bb2d-e85ba38ff7e8.png)
  ![image](https://user-images.githubusercontent.com/100524815/170909372-324abffe-0c6e-4489-a4fe-03099b0454d3.png)
  ![image](https://user-images.githubusercontent.com/100524815/170909471-395a7ad2-b951-4dbd-90ce-85fb58a4f7a5.png)
  ![image](https://user-images.githubusercontent.com/100524815/170909562-eb65f6cc-1554-41e6-8db0-42ea380471f0.png)
#### Mô tả chung:
  * Kế thừa game Super Mario Bros cổ điển, trong phiên bản game này, người chơi sẽ nhập vai Mario vượt qua chặng đường đầy vực sâu, các chướng ngại vật và các sinh vật tấn công để giải cứu công chúa. Game có 2 chế độ để người chơi lựa chọn: Classic World và Custom World. 
    * **Chế độ Classic World gồm 4 level từ 1 đến 4**
  ![image](https://user-images.githubusercontent.com/100524815/170910561-9f2af373-88bf-4068-a934-d167836619f3.png)
    * **Chế độ Custom World có 2 bối cảnh để người chơi lựa chọn là: Winter World và Summer World**
  ![image](https://user-images.githubusercontent.com/100524815/170910598-12c10a48-9e43-4486-b762-d461841340be.png)
  ![image](https://user-images.githubusercontent.com/100524815/170910632-bbbe2fd2-3dc0-4826-9a64-965b01c4f6ec.png) <br> 
  Mario cần đến được cột cờ ở cuối mỗi màn chơi để chiến thắng màn chơi đó. Khi bắt đầu chơi, Mario sẽ có 3 mạng, mỗi lần chạm phải sinh vật tấn công hoặc rơi xuống vực sẽ mất 1 mạng và phải chơi lại từ đầu của level.
  * Trên đường tới lâu đài của công chúa, Mario sẽ cố gắng tiêu diệt các sinh vật tấn công bằng cách nhảy lên đầu chúng để được cộng điểm, cố gắng thu thập thật nhiều đồng xu nằm rải rác trên đường và nhảy lên đánh vào các viên gạch (nhất là những viên gạch có dấu chấm hỏi) để thu thập đồng xu hoặc vật phẩm đặc biệt giấu trong chúng. Có 3 loại vật phẩm đặc biệt là:
    * Super Mushroom  ![mushroom_red](https://user-images.githubusercontent.com/100524815/170914186-d971017a-8a43-4ce5-90e4-71e3a580f3af.png) ![mushroom_green](https://user-images.githubusercontent.com/100524815/170914253-8cad14cb-1ea7-4551-afe1-8dc900d5d010.png)  ![mushroom_purple](https://user-images.githubusercontent.com/100524815/170914282-08824216-a5b1-4c56-b9fe-0b3d9278ccbc.png) : Khi ăn được Super Mushroom, tùy vào loại nấm mà Mario có thể được cộng thêm 1 mạng hoặc trở thành Super Mario - lớn gấp đôi kích thước ban đầu và có khả năng phá vỡ những viên gạch ở phía trên anh ấy. Khi bị sinh vật tấn công đụng trúng trong trạng thái Super Mario, Mario sẽ trở về kích thước bình thường chứ không chết.
    * Fire Flower  ![flower1](https://user-images.githubusercontent.com/100524815/170915117-27378afc-d2bb-4cc1-b11e-e96ee448aa89.png) : Khi ăn được Fire Flower, Mario sẽ chuyển thành Fire Mario - có khả năng bắn ra các quả cầu lửa để tiêu diệt kẻ thù.
    * Super Star  ![star3](https://user-images.githubusercontent.com/100524815/170915565-0eb29523-7d02-40a9-9451-6289489b6efa.png) : Khi ăn được Super Star, Mario sẽ chuyển sang trạng thái Immortal (bất tử) và dễ dàng tiêu diệt kẻ thù bằng cách đơn giản là chạm vào chúng, tuy nhiên trạng thái này chỉ là tạm thời và sẽ hết tác dụng sau một thời gian ngắn.







  
 
 
