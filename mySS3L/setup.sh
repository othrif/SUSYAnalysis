setupATLAS
localSetupDQ2Client --quiet
localSetupFAX --skipConfirm

localSetupPandaClient currentJedi --noAthenaCheck

setupATLAS
rcSetup -u
rcSetup Base,2.4.29

rc find_packages
rc clean
rc compile
