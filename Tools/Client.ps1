############################################################################
#                                                                          #
#        PROPRIETARY NOTICE                                                #
#                                                                          #
# These coded instructions, statements, and computer programs contain      #
# proprietary information of the Visual Urlang project, and are protected  #
# under copyright law. They may not be distributed, copied, or used except #
# under the provisions of the terms of the End-User License Agreement, in  #
# the file "EULA.md", which should have been included with this file.      #
#                                                                          #
#        Copyright Notice                                                  #
#                                                                          #
#    (c) 2020 The Visual Urlang Project.                                   #
#              All rights reserved.                                        #
############################################################################

[CmdletBinding(PositionalBinding=$false)]

param (
    [switch]$format,
    [string][Alias('ws')]$workspace = $( Get-Location ),
    [string]$vsDirectory = "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Tools\Llvm\bin",

    [parameter(ValueFromRemainingArguments=$true)][string[]]$properties)

function FormatSrc()
{
    Write-Host "=== Formatting Source ==="
    foreach($file in get-childitem -recurse -include *.cpp,*.h,*.cxx | `
            ? { $_.FullName -inotmatch 'Debug' } | `
            ? { $_.FullName -inotmatch 'lempar' } )
    {
        & $ClangFormat -i $file
    }
}

pushd .

$ClangFormat = "$($vsDirectory)\clang-format.exe"

if ($format)
{
    FormatSrc
}

popd