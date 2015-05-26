#!/bin/csh

foreach d (*)

/usr/bin/xcodebuild -project ./$d/$d.xcodeproj -configuration Deployment 

end
