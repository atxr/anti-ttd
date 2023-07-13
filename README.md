# anti-ttd
Different method to detect (or not) TTD.exe.

- ParentProcessName: checks if the parent process name is "ttd.exe"
> Can be improved by checking if TTDRecord.dll is loaded in the parent process
>

- PageGuard: triggers a page guard fault
- DebugFilterState: checks if debug priviledges are set