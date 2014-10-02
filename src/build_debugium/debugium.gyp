{
  'targets': [
    {
      'target_name': 'All',
      'type': 'none',
      'dependencies': [
        '../content/browser/devtools/devtools_resources.gyp:devtools_resources',
        '../content/browser/devtools/devtools.gyp:devtools_protocol_handler'
      ], #dependencies
    } # target_name: debugium_extra_resources
  ], # targets
}
