# echo "cleanup MiniNtuple MiniNtuple-HEAD in /afs/cern.ch/user/o/othrif/testarea/20.7.3"

if ( $?CMTROOT == 0 ) then
  setenv CMTROOT /cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc48-opt/20.7.3/CMT/v1r25p20140131
endif
source ${CMTROOT}/mgr/setup.csh
set cmtMiniNtupletempfile=`${CMTROOT}/${CMTBIN}/cmt.exe -quiet build temporary_name`
if $status != 0 then
  set cmtMiniNtupletempfile=/tmp/cmt.$$
endif
${CMTROOT}/${CMTBIN}/cmt.exe cleanup -csh -pack=MiniNtuple -version=MiniNtuple-HEAD -path=/afs/cern.ch/user/o/othrif/testarea/20.7.3  $* >${cmtMiniNtupletempfile}
if ( $status != 0 ) then
  echo "${CMTROOT}/${CMTBIN}/cmt.exe cleanup -csh -pack=MiniNtuple -version=MiniNtuple-HEAD -path=/afs/cern.ch/user/o/othrif/testarea/20.7.3  $* >${cmtMiniNtupletempfile}"
  set cmtcleanupstatus=2
  /bin/rm -f ${cmtMiniNtupletempfile}
  unset cmtMiniNtupletempfile
  exit $cmtcleanupstatus
endif
set cmtcleanupstatus=0
source ${cmtMiniNtupletempfile}
if ( $status != 0 ) then
  set cmtcleanupstatus=2
endif
/bin/rm -f ${cmtMiniNtupletempfile}
unset cmtMiniNtupletempfile
exit $cmtcleanupstatus

