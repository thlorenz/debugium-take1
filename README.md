# debugium

Attempt at pulling out chromium debugger to use it with Node.js.

## Sources

```
./src                                 https://chromium.googlesource.com/chromium/src
      /build                          https://chromium.googlesource.com/chromium/src/build
      /third_party
      |           /WebKit             https://chromium.googlesource.com/chromium/blink
      |
      /tools
            /grit                     https://chromium.googlesource.com/external/grit-i18n.git
            /gyp                      https://chromium.googlesource.com/external/gyp.git
```

## Dependencies

### Main Target

```
./src/chrome/debugium_resources.gyp
  :debugium_extra_resources
    - ./src/content/browser/devtools/devtools_resources.gyp:devtools_resources
```

### Resource/Code Generators

#### Most need

- `./src/build/grit_target.gypi`


#### Targets

##### devtools resources

```
./src/content/browser/devtools/devtools_resources.gyp
  :devtools_resources
    @devtools_resources
      - ./src/third_party/WebKit/public/blink_devtools.gyp:blink_generate_devtools_grd
      - ./src/tools/grit/grit.py
    @devtools_protocol_constants
      - ./src/third_party/WebKit/Source/devtools/protocol.json
      - ./src/third_party/WebKit/public/browser/devtools_protocol_constants_generator.py

./src/third_party/WebKit/public/blink_devtools.gyp
  :blink_generate_devtools_grd
    - ./src/third_party/WebKit/Source/devtools/devtools.gyp:generate_devtools_grd
  :devtools_protocol_constants
    - ./src/third_party/WebKit/Source/devtools/protocol.json
    - ./src/content/browser/devtools/browser_protocol.json
    - ./src/content/public/browser/devtools_protocol_constants_generator.py

./src/third_party/WebKit/public/blink_devtools.gyp
  :blink_generate_devtools_grd
    - ./src/third_party/WebKit/Source/devtools/devtools.gyp:generate_devtools_grd

./src/third_party/WebKit/Source/devtools/devtools.gyp
  :generate_devtools_grd
    - ./src/third_party/WebKit/Source/devtools/devtools.gypi
    :devtools_frontend_resources
    :devtools_html
    :toolbox_html
    :devtools_extension_api
    - ./src/third_party/WebKit/Source/devtools/scripts/generate_devtools_grd.py
  :devtools_frontend_resources
    :build_applications
    :devtools_html
    :toolbox_html
    :supported_css_properties
    :frontend_protocol_sources
  :build_applications
    :devtools_html
    :toolbox_html
    :supported_css_properties
    :frontend_protocol_sources
    - ./src/third_party/WebKit/Source/devtools/scripts/build_applications.py
    - ./src/third_party/WebKit/Source/devtools/scripts/modular_build.py
    - ./src/third_party/WebKit/Source/devtools/scripts/concatenate_application_code.py
  :devtools_html
    - ./src/third_party/WebKit/Source/devtools/front_end/devtools.html
    - ./src/third_party/WebKit/Source/devtools/scripts/generate_devtools_html.py
  :toolbox_html
    - ./src/third_party/WebKit/Source/devtools/front_end/toolbox.html
    - ./src/third_party/WebKit/Source/devtools/scripts/generate_devtools_html.py
  :supported_css_properties
    - ./src/third_party/WebKit/Source/devtools/scripts/generate_supported_css.py
    - ./src/third_party/WebKit/Source/core/css/CSSProperties.in
  :frontend_protocol_sources
    - ./src/third_party/WebKit/Source/devtools/scripts/CodeGeneratorFrontend.py
    - ./src/third_party/WebKit/Source/devtools/protocol.json
  :devtools_extension_api
    - ./src/third_party/WebKit/Source/devtools/scripts/generate_devtools_extension_api.py
    
./src/third_party/WebKit/Source/devtools/devtools.gypi
  - ./src/third_party/WebKit/Source/devtools/frontend/*
```

## License

MIT