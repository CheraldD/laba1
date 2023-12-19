#include <iostream>
#include <UnitTest++/UnitTest++.h>
#include "includer.h"
struct KeyB_fixture {
    modAlphaCipher * p;
    KeyB_fixture()
    {
        p = new modAlphaCipher(L"В");
    }
    ~KeyB_fixture()
    {
        delete p;
    }
};

SUITE(modAlpha_test)
{
    SUITE(KeyTest) {
        TEST(ValidKey) {
            CHECK_EQUAL(L"АБВАБ",modAlphaCipher(L"АБВ").encrypt(L"ААААА"));
        }
        TEST(LongKey) {
            CHECK_EQUAL(L"АБВГД",modAlphaCipher(L"АБВГДЕЁЖЗИ").encrypt(L"ААААА"));
        }
        TEST(LowCaseKey) {
            CHECK_EQUAL(L"БВГБВ",modAlphaCipher(L"бвг").encrypt(L"ААААА"));
        }
        TEST(DigitsInKey) {
            CHECK_THROW(modAlphaCipher cp(L"Б1"),cipher_error);
        }
        TEST(PunctuationInKey) {
            CHECK_THROW(modAlphaCipher cp(L"Б,Г"),cipher_error);
        }
        TEST(WhitespaceInKey) {
            CHECK_THROW(modAlphaCipher cp(L"Б Г"),cipher_error);
        }
        TEST(EmptyKey) {
            CHECK_THROW(modAlphaCipher cp(L""),cipher_error);
        }
        TEST(WeakKey) {
            CHECK_THROW(modAlphaCipher cp(L"ААА"),cipher_error);
        }
        TEST(KeyFromWrongAlphabet) {
            CHECK_THROW(modAlphaCipher cp(L"ABC"),cipher_error);
        }
    }
    SUITE(EncryptTest) {
        TEST_FIXTURE(KeyB_fixture, UpCaseString) {
            CHECK_EQUAL(L"СРЖЪЮЯФЛЧЦТВПШХКУМЛЧГХНРМ",
                        p->encrypt(L"ПОЕШЬЭТИХФРАНЦУЗСКИХБУЛОК"));
        }
        TEST_FIXTURE(KeyB_fixture, LowCaseString) {
            CHECK_EQUAL(L"СРЖЪЮЯФЛЧЦТВПШХКУМЛЧГХНРМ",
                        p->encrypt(L"поешьэтихфранцузскихбулок"));
        }
        TEST_FIXTURE(KeyB_fixture, StringWithWhitspaceAndPunct) {
            CHECK_EQUAL(L"СРЖЪЮЯФЛЧЦТВПШХКУМЛЧГХНРМ",
                        p->encrypt(L"поешь этих французских булок !!!"));
        }
        TEST_FIXTURE(KeyB_fixture, StringWithNumbers) {
            CHECK_EQUAL("IBQQZOFXZFBS", p->encrypt("Happy New 2019 Year"));
        }
        TEST_FIXTURE(KeyB_fixture, EmptyString) {
            CHECK_THROW(p->encrypt(L""),cipher_error);
        }
        TEST_FIXTURE(KeyB_fixture, NoAlphaString) {
            CHECK_THROW(p->encrypt(L"1234+8765=9999"),cipher_error);
        }
        TEST(MaxShiftKey) {
            CHECK_EQUAL(L"ОНДЧЫЬСЗФУПЯМХТЖРИЗФАТКНИ",
                        modAlphaCipher(L"Я").encrypt(L"ПОЕШЬЭТИХФРАНЦУЗСКИХБУЛОК"));
        }
    }
    SUITE(DecryptText) {
        TEST_FIXTURE(KeyB_fixture, UpCaseString) {
            CHECK_EQUAL("THEQUICKBROWNFOXJUMPSOVERTHELAZYDOG",
                        p->decrypt("UIFRVJDLCSPXOGPYKVNQTPWFSUIFMBAZEPH"));
        }
        TEST_FIXTURE(KeyB_fixture, LowCaseString) {
            CHECK_THROW(p->decrypt("uifRVJDLCSPXOGPYKVNQTPWFSUIFMBAZEPH"),cipher_error);
        }
        TEST_FIXTURE(KeyB_fixture, WhitespaceString) {
            CHECK_THROW(p->decrypt("UIF RVJDL CSPXO GPY KVNQT PWFS UIF MBAZ EPH"),cipher_error);
        }
        TEST_FIXTURE(KeyB_fixture, DigitsString) {
            CHECK_THROW(p->decrypt("IBQQZOFX2019ZFBS"),cipher_error);
        }
        TEST_FIXTURE(KeyB_fixture, PunctString) {
            CHECK_THROW(p->decrypt("IFMMP,XPSME"),cipher_error);
        }
        TEST_FIXTURE(KeyB_fixture, EmptyString) {
            CHECK_THROW(p->decrypt(""),cipher_error);
        }
        TEST(MaxShiftKey) {
            CHECK_EQUAL("THEQUICKBROWNFOXJUMPSOVERTHELAZYDOG",
                        modAlphaCipher("Z").decrypt("SGDPTHBJAQNVMENWITLORNUDQSGDKZYXCNF"));
        }
    }
}
