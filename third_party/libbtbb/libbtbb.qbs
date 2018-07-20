import qbs 1.0
import qbs.TextFile
import qbs.FileInfo

 CppApplication {
    type: "staticlibrary"

    cpp.cxxLanguageVersion: "c++11"

    files: [
        "src/lib/**",
]

    cpp.includePaths: [""]

    cpp.defines: [
//        "BOOST_NO_CXX11_RVALUE_REFERENCES=0",
//        "BOOST_NO_CXX11_SMART_PTR=0"
    ]

    cpp.commonCompilerFlags: []

    cpp.cxxFlags: ["-std=c++11"]

    cpp.linkerFlags: ["-Wall"]

    cpp.libraryPaths: []

    cpp.dynamicLibraries: ["boost_system", "gnuradio-analog", "gnuradio-runtime", "gnuradio-pmt", "gnuradio-blocks", "gnuradio-filter", "volk", "gnuradio-osmosdr", "gnuradio-fft"]

    Export {

        Depends {
            name: "cpp"
        }

        cpp.includePaths: ["src/lib/src"]
    }

    Group {
        // Properties for the produced executable
        fileTagsFilter: product.type
        qbs.install: false
    }
}
