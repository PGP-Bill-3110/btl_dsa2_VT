
#include "app/inventory.h"
// // -------------------- InventoryManager Method Definitions --------------------
InventoryManager::InventoryManager()
{
    // TODO
    // Khởi tạo các thành phần rỗng
    attributesMatrix = List2D<InventoryAttribute>();
    productNames = List1D<string>();
    quantities = List1D<int>();
}

InventoryManager::InventoryManager(const List2D<InventoryAttribute> &matrix,
                                   const List1D<string> &names,
                                   const List1D<int> &quantities)
{
    // TODO
    //Sao chép dữ liệu từ các tham số
    this->attributesMatrix = matrix;
    this->productNames = names;
    this->quantities = quantities;
}

InventoryManager::InventoryManager(const InventoryManager &other)
{
    // TODO
    // Sao chép dữ liệu từ đối tượng khác
    this->attributesMatrix = other.attributesMatrix;
    this->productNames = other.productNames;
    this->quantities = other.quantities;
}

int InventoryManager::size() const
{
    // TODO
    return productNames.size();
}

List1D<InventoryAttribute> InventoryManager::getProductAttributes(int index) const
{
    // TODO
    return attributesMatrix.getRow(index);
}

string InventoryManager::getProductName(int index) const
{
    // TODO
    return productNames.get(index);
}

int InventoryManager::getProductQuantity(int index) const
{
    // TODO
    return quantities.get(index);
}

void InventoryManager::updateQuantity(int index, int newQuantity)
{
    // TODO
    quantities.set(index, newQuantity);
}

void InventoryManager::addProduct(const List1D<InventoryAttribute> &attributes, const string &name, int quantity)
{
    // TODO
    attributesMatrix.setRow(attributesMatrix.rows(), attributes);
    productNames.add(name);
    quantities.add(quantity);
}

void InventoryManager::removeProduct(int index)
{
    // TODO
    attributesMatrix.removeAt(index);
    productNames.removeAt(index);
    quantities.removeAt(index);
}


//! tăng dần của cái gì
/* List1D<string> InventoryManager::query(int attributeIndex, const double &minValue,
                                       const double &maxValue, int minQuantity, bool ascending) const
{
    // TODO

    List1D<string> result;
    List1D<double> attributeValues;

    // Thu thập dữ liệu thỏa điều kiện
    for (int i = 0; i < attributesMatrix.rows(); i++) {
        double attributeValue = attributesMatrix.get(i, attributeIndex).value;
        int productQuantity = quantities.get(i);

        if (attributeValue >= minValue && attributeValue <= maxValue && productQuantity >= minQuantity) {
            result.add(productNames.get(i));
            attributeValues.add(attributeValue);
        }
    }

    // Sắp xếp thủ công bằng Selection Sort
    int n = result.size();
    for (int i = 0; i < n - 1; i++) {
        int targetIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (ascending) {
                if (attributeValues.get(j) < attributeValues.get(targetIndex)) {
                    targetIndex = j;
                }
            } else {
                if (attributeValues.get(j) > attributeValues.get(targetIndex)) {
                    targetIndex = j;
                }
            }
        }

        // Hoán đổi dữ liệu trong List1D mà không dùng std::swap
        if (targetIndex != i) {
            string tempName = result.get(i);
            double tempValue = attributeValues.get(i);

            result.set(i, result.get(targetIndex));
            attributeValues.set(i, attributeValues.get(targetIndex));

            result.set(targetIndex, tempName);
            attributeValues.set(targetIndex, tempValue);
        }
    }

    return result;

} */


List1D<string> InventoryManager::query(string attributeName, const double &minValue,
                                       const double &maxValue, int minQuantity, bool ascending) const
{
    List1D<string> result;
    List1D<double> attributeValues;

    // Duyệt qua từng sản phẩm trong kho
    for (int i = 0; i < attributesMatrix.rows(); i++) {
        List1D<InventoryAttribute> productAttributes = attributesMatrix.getRow(i);

        // Tìm thuộc tính có tên trùng với `attributeName`
        for (int j = 0; j < productAttributes.size(); j++) {
            InventoryAttribute attr = productAttributes.get(j);

            if (attr.name == attributeName) { 
                // Kiểm tra điều kiện giá trị thuộc tính và số lượng tồn kho
                double attributeValue = attr.value;
                int productQuantity = quantities.get(i);

                if (attributeValue >= minValue && attributeValue <= maxValue &&
                    productQuantity >= minQuantity) 
                {
                    result.add(productNames.get(i));
                    attributeValues.add(attributeValue);
                }
                break;  // Thoát vòng lặp sau khi tìm thấy thuộc tính khớp
            }
        }
    }

    // Sắp xếp thủ công bằng Selection Sort
    int n = result.size();
    for (int i = 0; i < n - 1; i++) {
        int targetIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (ascending) {
                if (attributeValues.get(j) < attributeValues.get(targetIndex)) {
                    targetIndex = j;
                }
            } else {
                if (attributeValues.get(j) > attributeValues.get(targetIndex)) {
                    targetIndex = j;
                }
            }
        }

        // Hoán đổi dữ liệu trong List1D mà không dùng std::swap
        if (targetIndex != i) {
            string tempName = result.get(i);
            double tempValue = attributeValues.get(i);

            result.set(i, result.get(targetIndex));
            attributeValues.set(i, attributeValues.get(targetIndex));

            result.set(targetIndex, tempName);
            attributeValues.set(targetIndex, tempValue);
        }
    }

    return result;
}



void InventoryManager::removeDuplicates()
{
    // TODO
    for (int i = 0; i < attributesMatrix.rows(); i++) {
        for (int j = i + 1; j < attributesMatrix.rows(); j++) {
            if (attributesMatrix.getRow(i).toString() == attributesMatrix.getRow(j).toString() &&
                productNames.get(i) == productNames.get(j)) {
                int newQuantity = quantities.get(i) + quantities.get(j);
                quantities.set(i, newQuantity);
                removeProduct(j);
                j--; // Kiểm tra lại vị trí j sau khi xóa phần tử
            }
        }
    }
}
//! Hàm này có gọi removeDuplicates hay không
InventoryManager InventoryManager::merge(const InventoryManager &inv1,
                                         const InventoryManager &inv2)
{
    // TODO

    InventoryManager mergedInventory = inv1;
    for (int i = 0; i < inv2.size(); i++) {
        mergedInventory.addProduct(inv2.getProductAttributes(i),
                                   inv2.getProductName(i),
                                   inv2.getProductQuantity(i));
    }
    mergedInventory.removeDuplicates();
    return mergedInventory;

}

void InventoryManager::split(InventoryManager &section1,
                             InventoryManager &section2,
                             double ratio) const
{
    // TODO
    int totalSize = size();
    int section1Size = static_cast<int>((totalSize * ratio) + 0.5); // Làm tròn chuẩn xác hơn

    for (int i = 0; i < section1Size; i++) {
        section1.addProduct(getProductAttributes(i), getProductName(i), getProductQuantity(i));
    }
    for (int i = section1Size; i < totalSize; i++) {
        section2.addProduct(getProductAttributes(i), getProductName(i), getProductQuantity(i));
    }
}

List2D<InventoryAttribute> InventoryManager::getAttributesMatrix() const
{
    // TODO
    return attributesMatrix;
}

List1D<string> InventoryManager::getProductNames() const
{
    // TODO
    return productNames;
}

List1D<int> InventoryManager::getQuantities() const
{
    // TODO
   return quantities;
}

string InventoryManager::toString() const
{
    // TODO
    stringstream ss;
    ss << "InventoryManager[\n";
    ss << "  AttributesMatrix: " << attributesMatrix.toString() << ",\n";
    ss << "  ProductNames: " << productNames.toString() << ",\n";
    ss << "  Quantities: " << quantities.toString() << "\n";
    ss << "]";
    return ss.str();
}
