# echo "setup MiniNtuple MiniNtuple-HEAD in /afs/cern.ch/user/o/othrif/testarea/20.7.3"

if test "${CMTROOT}" = ""; then
  CMTROOT=/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc48-opt/20.7.3/CMT/v1r25p20140131; export CMTROOT
fi
. ${CMTROOT}/mgr/setup.sh
cmtMiniNtupletempfile=`${CMTROOT}/${CMTBIN}/cmt.exe -quiet build temporary_name`
if test ! $? = 0 ; then cmtMiniNtupletempfile=/tmp/cmt.$$; fi
${CMTROOT}/${CMTBIN}/cmt.exe setup -sh -pack=MiniNtuple -version=MiniNtuple-HEAD -path=/afs/cern.ch/user/o/othrif/testarea/20.7.3  -no_cleanup $* >${cmtMiniNtupletempfile}
if test $? != 0 ; then
  echo >&2 "${CMTROOT}/${CMTBIN}/cmt.exe setup -sh -pack=MiniNtuple -version=MiniNtuple-HEAD -path=/afs/cern.ch/user/o/othrif/testarea/20.7.3  -no_cleanup $* >${cmtMiniNtupletempfile}"
  cmtsetupstatus=2
  /bin/rm -f ${cmtMiniNtupletempfile}
  unset cmtMiniNtupletempfile
  return $cmtsetupstatus
fi
cmtsetupstatus=0
. ${cmtMiniNtupletempfile}
if test $? != 0 ; then
  cmtsetupstatus=2
fi
/bin/rm -f ${cmtMiniNtupletempfile}
unset cmtMiniNtupletempfile
return $cmtsetupstatus

