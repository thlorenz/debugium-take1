{
  'targets': [
    {
      'target_name': 'All',
      'type': 'none',
      'dependencies': [
        'frontend_resources',
        'backend_resources'
      ], #dependencies
    }, # target: All
    {
      'target_name': 'frontend_resources',
      'type': 'none',
      'dependencies': [
        '../content/browser/devtools/devtools_resources.gyp:devtools_resources',
        '../content/browser/devtools/devtools.gyp:devtools_protocol_handler',
      ],
    }, # target: frontend_resources
    {
      'target_name': 'backend_resources',
      'type': 'none',
      'dependencies': [
        '../third_party/WebKit/Source/core/core.gyp:inspector_protocol_sources',
        '../third_party/WebKit/Source/core/core_generated.gyp:make_core_generated',
        '../third_party/WebKit/Source/wtf/wtf.gyp:wtf'
      ]
    } # target: frontend_resources
  ], # targets
}
