{
  'targets': [
    { # GN version: //debugium:extra_resources
      'target_name': 'debugium_extra_resources',
      'type': 'none',
      'conditions': [
        ['OS != "ios"', {
          'dependencies': [
            '../content/browser/devtools/devtools_resources.gyp:devtools_resources',
          ],
        }],
      ]
    } # target_name: debugium_extra_resources
  ], # targets
}
