#include "pch.h"
#include "serialWrite_h.h"
#if __has_include("serialWrite_h.g.cpp")
#include "serialWrite_h.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::serialPrint::implementation
{
    int32_t serialWrite_h::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void serialWrite_h::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void serialWrite_h::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
        Button().Content(box_value(L"Clicked"));
    }
}
