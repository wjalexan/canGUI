#pragma once

#include "serialWrite_h.g.h"

namespace winrt::serialPrint::implementation
{
    struct serialWrite_h : serialWrite_hT<serialWrite_h>
    {
        serialWrite_h() 
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void ClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::serialPrint::factory_implementation
{
    struct serialWrite_h : serialWrite_hT<serialWrite_h, implementation::serialWrite_h>
    {
    };
}
