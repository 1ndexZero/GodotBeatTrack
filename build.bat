scons platform=windows target=template_debug
scons platform=windows target=template_release
xcopy /Y /I "project\addons\beat_track\bin\*" "E:\Projects\aud-editor\addons\beat_track\bin\"