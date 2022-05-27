# kodiak
A small "backdoor" that implements keylogging and other
 surveillance methods.
# Disclaimer
Some features are still being implemented or are only in "idea" phase
# Features
- dynamic payload hiding with randomized file system search depth for ideal spot
- keepalive (can't be killed from task manager)
- keylogger, and yet unimplemented audio passthrough and screencaps
- uses self written telegram library for reliabilty and small size (though this will be migrated to the [[MATRIX]](https://spec.matrix.org/latest/) protocol)
- polymorphic payload (has multiple installation options depending on available privileges and privilege escalation attempts) 
- 23 kb standalone exe and a 17kb dll for hooks and other external payloads (total final payload size 50kb)
