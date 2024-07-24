#ifndef DESKXIUXINA_ENCRYPT_VALUS_H
#define DESKXIUXINA_ENCRYPT_VALUS_H

class EncryptionInt
{
private:
    int units;              ///< 个位
    int tens;               ///< 十位
    int hundreds;           ///< 百位
    int thousands;          ///< 千位
    int ten_thousands;      ///< 万位
    int hundred_thousands;  ///< 十万位
    int millions;           ///< 百万位
    int ten_millions;       ///< 千万位
    int billions;           ///< 亿位

public:
    void ValueEncryption(int value)
    {
        units = value % 10;
        tens = (value / 10) % 10;
        hundreds = (value / 100) % 10;
        thousands = (value / 1000) % 10;
        ten_thousands = (value / 10000) % 10;
        hundred_thousands = (value / 100000) % 10;
        millions = (value / 1000000) % 10;
        ten_millions = (value / 10000000) % 10;
        billions = (value / 100000000) % 10;
    }

    int ValueDecrypt()
    {
        return units + tens * 10 + hundreds * 100 + thousands * 1000 + ten_thousands * 10000 + hundred_thousands * 100000 + millions * 1000000 + ten_millions * 10000000 + billions * 100000000;
    }

    bool CheckData()
    {
        return (units < 10 && tens < 10 && hundreds < 10 && thousands < 10 && ten_thousands < 10 && hundred_thousands < 10 && millions < 10 && ten_millions < 10 && billions < 10);
    }

    // 公有成员函数，用于获取私有成员变量的值
    int getUnits() { return units; }
    int getTens() { return tens; }
    int getHundreds() { return hundreds; }
    int getThousands() { return thousands; }
    int getTenThousands() { return ten_thousands; }
    int getHundredThousands() { return hundred_thousands; }
    int getMillions() { return millions; }
    int getTenMillions() { return ten_millions; }
    int getBillions() { return billions; }
};




#endif //DESKXIUXINA_ENCRYPT_VALUS_H
