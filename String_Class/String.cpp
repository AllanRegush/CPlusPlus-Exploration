#include <cstdint>
#include <cstring>
#include <cstdlib>
#include <iostream>

class String {
public:
    String(const char *str) noexcept
    {
        m_size = strlen(str);
        m_str = (char *)(malloc(m_size + 1));
        strcpy(m_str, str);
    }
    ~String()
    {
        free(m_str);
    }
    constexpr size_t size() const
    {
        return m_size;
    }
    constexpr bool empty() const
    {
        return m_size > 0 ? false : true; 
    }
    constexpr char * c_str() const 
    {
        return m_str;
    }
    friend std::ostream& operator<<(std::ostream& os, const String& str);
private:
    std::size_t m_size { 0 };
    char *m_str;
};

std::ostream& operator<<(std::ostream& os, const String& str)
{
    os << str.c_str();
    return os;
}


int main(int argc, char **argv) 
{
    String str = "Hello, World";
    String empty = "";
    std::cout << "String: " << str << " Size: " << str.size() <<  " isEmpty? : " << str.empty() << '\n';
    std::cout << empty.empty() << '\n';
    return 0;
}
