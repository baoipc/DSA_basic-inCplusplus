# Cây

## Định nghĩa chung

Tập hợp T phần tử (được gọi là các nút của cây). Trong một cây, sẽ có một nút đặc biệt làm gốc, các nút còn lại chia thành các tập rời nhau theo quan hệ phân cấp, T~i~ cũng được gọi là một cây. Mỗi nút ở cấp i sẽ quản lí một số nút ở cấp i+1.Quan hệ này gọi là cha-con

## Một số khái niệm

- Bậc của nút: Số cây con của nút đó
- Bậc của cây: Bậc lớn nhất của nút trong cây đó
- Nút gốc: Nút không có cha
- Nút lá: Nút có bậc bằng 0
- Mức một nút:
  
  - Mức (gốc T) = 0
  - Mức T~1~ = Mức T~2~ = ... = Mức T~n~ = Mức T~0~ +1
  - Độ dài đường đi từ gốc đến nút x : là số nhánh cần đi qua kể từ gốc đến x
  - Chiều cao (hay còn gọi là chiều sâu): số mức lớn nhất của nút con trên cây đó

## Các loại cây

### Cây nhị phân - Binary Tree

[Read here](BinaryTree/README.md)

### Cây tìm kiếm nhị phân - Binary Search Tree

[Read here](BinarySearchTree/README.md)

### Cây nhị phân tìm kiếm tự cân bằng - AVL Tree

[Read here](AVL_Tree/README.md)
