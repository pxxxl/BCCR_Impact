{
    files = {
        [[build\.objs\main\windows\x86\release\main.c.obj]],
        [[build\windows\x86\release\BCCR_Impact.lib]]
    },
    values = {
        [[E:\1_IDE\VisualStudio\VC\Tools\MSVC\14.35.32215\bin\HostX86\x86\link.exe]],
        {
            "-nologo",
            "-dynamicbase",
            "-nxcompat",
            "-machine:x86",
            [[-libpath:build\windows\x86\release]],
            "/opt:ref",
            "/opt:icf",
            "BCCR_Impact.lib"
        }
    }
}