
    printf("fileName:     %s\n", params.fileName);
    printf("pipeFile:     %s\n", params.pipeFile);
    printf("testFile:     %s\n", params.testFile);

    printf("dir:          %s\n", params.dir);
    printf("outName:      %s\n", params.outName);

    printf("watch:        %d\n", params.watch);
    printf("run:          %d\n", params.run);
    printf("sanitizer:    %d\n", params.sanitizer);

    printf("linkedLibs:   %d\n", params.compiler.linkedLibs);
    printf("debug:        %d\n", params.compiler.debug);
    printf("m32:          %d\n", params.compiler.m32);
    printf("math:         %d\n", params.compiler.math);
    printf("ejudge:       %d\n", params.compiler.ejudge);
    printf("compiler args: ");
    for (int i = 0; params.compiler.args[i]; i++)
        printf("\"%s\" ", params.compiler.args[i]);
    printf("\n");

    printf("hideInput:    %d\n", params.tester.hideInput);
    printf("dontTrimData: %d\n", params.tester.dontTrimData);
    printf("dontTrimAnsw: %d\n", params.tester.dontTrimAnsw);
    printf("onlyFailed:   %d\n", params.tester.onlyFailed);

    printf("noMsgs:       %d\n", params.noMsgs);
    printf("noWarnings:   %d\n", params.noWarnings);

    printf("args: ");
    for (int i = 0; params.args[i]; i++)
        printf("\"%s\" ", params.args[i]);
    printf("\n");
    printf("color: %d\n", params.color);

