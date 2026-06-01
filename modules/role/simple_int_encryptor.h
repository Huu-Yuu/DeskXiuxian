#ifndef DESKXIUXINA_SECURE_DATA_H
#define DESKXIUXINA_SECURE_DATA_H

/** @brief 加密器*/
class SimpleIntEncryptor
{
private:
    int key;

public:
    SimpleIntEncryptor(int key) : key(key) {}

    int Encrypt(int data)
    {
        return data ^ key;
    }

    int Decrypt(int encryptedData)
    {
        return encryptedData ^ key;
    }
};
#endif //DESKXIUXINA_SECURE_DATA_H
