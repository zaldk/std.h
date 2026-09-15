#ifndef STD_LINUX_TABLES_H
#define STD_LINUX_TABLES_H
/*
    taken from linux-7.2/arch/x86/entry/syscalls/syscall_64.tbl
    * removed the 'x32' entries
    * changed abi '64' to 'x64'
    * changed format to X-macro (https://en.wikipedia.org/wiki/X_macro)
    The format is: <syscall number> <name> <name but uppercase>
*/
#define SYSCALL_TABLE \
        X(0,   read,                    READ                    ) \
        X(1,   write,                   WRITE                   ) \
        X(2,   open,                    OPEN                    ) \
        X(3,   close,                   CLOSE                   ) \
        X(4,   stat,                    STAT                    ) \
        X(5,   fstat,                   FSTAT                   ) \
        X(6,   lstat,                   LSTAT                   ) \
        X(7,   poll,                    POLL                    ) \
        X(8,   lseek,                   LSEEK                   ) \
        X(9,   mmap,                    MMAP                    ) \
        X(10,  mprotect,                MPROTECT                ) \
        X(11,  munmap,                  MUNMAP                  ) \
        X(12,  brk,                     BRK                     ) \
        X(13,  rt_sigaction,            RT_SIGACTION            ) \
        X(14,  rt_sigprocmask,          RT_SIGPROCMASK          ) \
        X(15,  rt_sigreturn,            RT_SIGRETURN            ) \
        X(16,  ioctl,                   IOCTL                   ) \
        X(17,  pread64,                 PREAD64                 ) \
        X(18,  pwrite64,                PWRITE64                ) \
        X(19,  readv,                   READV                   ) \
        X(20,  writev,                  WRITEV                  ) \
        X(21,  access,                  ACCESS                  ) \
        X(22,  pipe,                    PIPE                    ) \
        X(23,  select,                  SELECT                  ) \
        X(24,  sched_yield,             SCHED_YIELD             ) \
        X(25,  mremap,                  MREMAP                  ) \
        X(26,  msync,                   MSYNC                   ) \
        X(27,  mincore,                 MINCORE                 ) \
        X(28,  madvise,                 MADVISE                 ) \
        X(29,  shmget,                  SHMGET                  ) \
        X(30,  shmat,                   SHMAT                   ) \
        X(31,  shmctl,                  SHMCTL                  ) \
        X(32,  dup,                     DUP                     ) \
        X(33,  dup2,                    DUP2                    ) \
        X(34,  pause,                   PAUSE                   ) \
        X(35,  nanosleep,               NANOSLEEP               ) \
        X(36,  getitimer,               GETITIMER               ) \
        X(37,  alarm,                   ALARM                   ) \
        X(38,  setitimer,               SETITIMER               ) \
        X(39,  getpid,                  GETPID                  ) \
        X(40,  sendfile,                SENDFILE                ) \
        X(41,  socket,                  SOCKET                  ) \
        X(42,  connect,                 CONNECT                 ) \
        X(43,  accept,                  ACCEPT                  ) \
        X(44,  sendto,                  SENDTO                  ) \
        X(45,  recvfrom,                RECVFROM                ) \
        X(46,  sendmsg,                 SENDMSG                 ) \
        X(47,  recvmsg,                 RECVMSG                 ) \
        X(48,  shutdown,                SHUTDOWN                ) \
        X(49,  bind,                    BIND                    ) \
        X(50,  listen,                  LISTEN                  ) \
        X(51,  getsockname,             GETSOCKNAME             ) \
        X(52,  getpeername,             GETPEERNAME             ) \
        X(53,  socketpair,              SOCKETPAIR              ) \
        X(54,  setsockopt,              SETSOCKOPT              ) \
        X(55,  getsockopt,              GETSOCKOPT              ) \
        X(56,  clone,                   CLONE                   ) \
        X(57,  fork,                    FORK                    ) \
        X(58,  vfork,                   VFORK                   ) \
        X(59,  execve,                  EXECVE                  ) \
        X(60,  exit,                    EXIT                    ) \
        X(61,  wait4,                   WAIT4                   ) \
        X(62,  kill,                    KILL                    ) \
        X(63,  uname,                   UNAME                   ) \
        X(64,  semget,                  SEMGET                  ) \
        X(65,  semop,                   SEMOP                   ) \
        X(66,  semctl,                  SEMCTL                  ) \
        X(67,  shmdt,                   SHMDT                   ) \
        X(68,  msgget,                  MSGGET                  ) \
        X(69,  msgsnd,                  MSGSND                  ) \
        X(70,  msgrcv,                  MSGRCV                  ) \
        X(71,  msgctl,                  MSGCTL                  ) \
        X(72,  fcntl,                   FCNTL                   ) \
        X(73,  flock,                   FLOCK                   ) \
        X(74,  fsync,                   FSYNC                   ) \
        X(75,  fdatasync,               FDATASYNC               ) \
        X(76,  truncate,                TRUNCATE                ) \
        X(77,  ftruncate,               FTRUNCATE               ) \
        X(78,  getdents,                GETDENTS                ) \
        X(79,  getcwd,                  GETCWD                  ) \
        X(80,  chdir,                   CHDIR                   ) \
        X(81,  fchdir,                  FCHDIR                  ) \
        X(82,  rename,                  RENAME                  ) \
        X(83,  mkdir,                   MKDIR                   ) \
        X(84,  rmdir,                   RMDIR                   ) \
        X(85,  creat,                   CREAT                   ) \
        X(86,  link,                    LINK                    ) \
        X(87,  unlink,                  UNLINK                  ) \
        X(88,  symlink,                 SYMLINK                 ) \
        X(89,  readlink,                READLINK                ) \
        X(90,  chmod,                   CHMOD                   ) \
        X(91,  fchmod,                  FCHMOD                  ) \
        X(92,  chown,                   CHOWN                   ) \
        X(93,  fchown,                  FCHOWN                  ) \
        X(94,  lchown,                  LCHOWN                  ) \
        X(95,  umask,                   UMASK                   ) \
        X(96,  gettimeofday,            GETTIMEOFDAY            ) \
        X(97,  getrlimit,               GETRLIMIT               ) \
        X(98,  getrusage,               GETRUSAGE               ) \
        X(99,  sysinfo,                 SYSINFO                 ) \
        X(100, times,                   TIMES                   ) \
        X(101, ptrace,                  PTRACE                  ) \
        X(102, getuid,                  GETUID                  ) \
        X(103, syslog,                  SYSLOG                  ) \
        X(104, getgid,                  GETGID                  ) \
        X(105, setuid,                  SETUID                  ) \
        X(106, setgid,                  SETGID                  ) \
        X(107, geteuid,                 GETEUID                 ) \
        X(108, getegid,                 GETEGID                 ) \
        X(109, setpgid,                 SETPGID                 ) \
        X(110, getppid,                 GETPPID                 ) \
        X(111, getpgrp,                 GETPGRP                 ) \
        X(112, setsid,                  SETSID                  ) \
        X(113, setreuid,                SETREUID                ) \
        X(114, setregid,                SETREGID                ) \
        X(115, getgroups,               GETGROUPS               ) \
        X(116, setgroups,               SETGROUPS               ) \
        X(117, setresuid,               SETRESUID               ) \
        X(118, getresuid,               GETRESUID               ) \
        X(119, setresgid,               SETRESGID               ) \
        X(120, getresgid,               GETRESGID               ) \
        X(121, getpgid,                 GETPGID                 ) \
        X(122, setfsuid,                SETFSUID                ) \
        X(123, setfsgid,                SETFSGID                ) \
        X(124, getsid,                  GETSID                  ) \
        X(125, capget,                  CAPGET                  ) \
        X(126, capset,                  CAPSET                  ) \
        X(127, rt_sigpending,           RT_SIGPENDING           ) \
        X(128, rt_sigtimedwait,         RT_SIGTIMEDWAIT         ) \
        X(129, rt_sigqueueinfo,         RT_SIGQUEUEINFO         ) \
        X(130, rt_sigsuspend,           RT_SIGSUSPEND           ) \
        X(131, sigaltstack,             SIGALTSTACK             ) \
        X(132, utime,                   UTIME                   ) \
        X(133, mknod,                   MKNOD                   ) \
        X(134, uselib,                  USELIB                  ) \
        X(135, personality,             PERSONALITY             ) \
        X(136, ustat,                   USTAT                   ) \
        X(137, statfs,                  STATFS                  ) \
        X(138, fstatfs,                 FSTATFS                 ) \
        X(139, sysfs,                   SYSFS                   ) \
        X(140, getpriority,             GETPRIORITY             ) \
        X(141, setpriority,             SETPRIORITY             ) \
        X(142, sched_setparam,          SCHED_SETPARAM          ) \
        X(143, sched_getparam,          SCHED_GETPARAM          ) \
        X(144, sched_setscheduler,      SCHED_SETSCHEDULER      ) \
        X(145, sched_getscheduler,      SCHED_GETSCHEDULER      ) \
        X(146, sched_get_priority_max,  SCHED_GET_PRIORITY_MAX  ) \
        X(147, sched_get_priority_min,  SCHED_GET_PRIORITY_MIN  ) \
        X(148, sched_rr_get_interval,   SCHED_RR_GET_INTERVAL   ) \
        X(149, mlock,                   MLOCK                   ) \
        X(150, munlock,                 MUNLOCK                 ) \
        X(151, mlockall,                MLOCKALL                ) \
        X(152, munlockall,              MUNLOCKALL              ) \
        X(153, vhangup,                 VHANGUP                 ) \
        X(154, modify_ldt,              MODIFY_LDT              ) \
        X(155, pivot_root,              PIVOT_ROOT              ) \
        X(156, _sysctl,                 _SYSCTL                 ) \
        X(157, prctl,                   PRCTL                   ) \
        X(158, arch_prctl,              ARCH_PRCTL              ) \
        X(159, adjtimex,                ADJTIMEX                ) \
        X(160, setrlimit,               SETRLIMIT               ) \
        X(161, chroot,                  CHROOT                  ) \
        X(162, sync,                    SYNC                    ) \
        X(163, acct,                    ACCT                    ) \
        X(164, settimeofday,            SETTIMEOFDAY            ) \
        X(165, mount,                   MOUNT                   ) \
        X(166, umount2,                 UMOUNT2                 ) \
        X(167, swapon,                  SWAPON                  ) \
        X(168, swapoff,                 SWAPOFF                 ) \
        X(169, reboot,                  REBOOT                  ) \
        X(170, sethostname,             SETHOSTNAME             ) \
        X(171, setdomainname,           SETDOMAINNAME           ) \
        X(172, iopl,                    IOPL                    ) \
        X(173, ioperm,                  IOPERM                  ) \
        X(174, create_module,           CREATE_MODULE           ) \
        X(175, init_module,             INIT_MODULE             ) \
        X(176, delete_module,           DELETE_MODULE           ) \
        X(177, get_kernel_syms,         GET_KERNEL_SYMS         ) \
        X(178, query_module,            QUERY_MODULE            ) \
        X(179, quotactl,                QUOTACTL                ) \
        X(180, nfsservctl,              NFSSERVCTL              ) \
        X(181, getpmsg,                 GETPMSG                 ) \
        X(182, putpmsg,                 PUTPMSG                 ) \
        X(183, afs_syscall,             AFS_SYSCALL             ) \
        X(184, tuxcall,                 TUXCALL                 ) \
        X(185, security,                SECURITY                ) \
        X(186, gettid,                  GETTID                  ) \
        X(187, readahead,               READAHEAD               ) \
        X(188, setxattr,                SETXATTR                ) \
        X(189, lsetxattr,               LSETXATTR               ) \
        X(190, fsetxattr,               FSETXATTR               ) \
        X(191, getxattr,                GETXATTR                ) \
        X(192, lgetxattr,               LGETXATTR               ) \
        X(193, fgetxattr,               FGETXATTR               ) \
        X(194, listxattr,               LISTXATTR               ) \
        X(195, llistxattr,              LLISTXATTR              ) \
        X(196, flistxattr,              FLISTXATTR              ) \
        X(197, removexattr,             REMOVEXATTR             ) \
        X(198, lremovexattr,            LREMOVEXATTR            ) \
        X(199, fremovexattr,            FREMOVEXATTR            ) \
        X(200, tkill,                   TKILL                   ) \
        X(201, time,                    TIME                    ) \
        X(202, futex,                   FUTEX                   ) \
        X(203, sched_setaffinity,       SCHED_SETAFFINITY       ) \
        X(204, sched_getaffinity,       SCHED_GETAFFINITY       ) \
        X(205, set_thread_area,         SET_THREAD_AREA         ) \
        X(206, io_setup,                IO_SETUP                ) \
        X(207, io_destroy,              IO_DESTROY              ) \
        X(208, io_getevents,            IO_GETEVENTS            ) \
        X(209, io_submit,               IO_SUBMIT               ) \
        X(210, io_cancel,               IO_CANCEL               ) \
        X(211, get_thread_area,         GET_THREAD_AREA         ) \
        X(212, lookup_dcookie,          LOOKUP_DCOOKIE          ) \
        X(213, epoll_create,            EPOLL_CREATE            ) \
        X(214, epoll_ctl_old,           EPOLL_CTL_OLD           ) \
        X(215, epoll_wait_old,          EPOLL_WAIT_OLD          ) \
        X(216, remap_file_pages,        REMAP_FILE_PAGES        ) \
        X(217, getdents64,              GETDENTS64              ) \
        X(218, set_tid_address,         SET_TID_ADDRESS         ) \
        X(219, restart_syscall,         RESTART_SYSCALL         ) \
        X(220, semtimedop,              SEMTIMEDOP              ) \
        X(221, fadvise64,               FADVISE64               ) \
        X(222, timer_create,            TIMER_CREATE            ) \
        X(223, timer_settime,           TIMER_SETTIME           ) \
        X(224, timer_gettime,           TIMER_GETTIME           ) \
        X(225, timer_getoverrun,        TIMER_GETOVERRUN        ) \
        X(226, timer_delete,            TIMER_DELETE            ) \
        X(227, clock_settime,           CLOCK_SETTIME           ) \
        X(228, clock_gettime,           CLOCK_GETTIME           ) \
        X(229, clock_getres,            CLOCK_GETRES            ) \
        X(230, clock_nanosleep,         CLOCK_NANOSLEEP         ) \
        X(231, exit_group,              EXIT_GROUP              ) \
        X(232, epoll_wait,              EPOLL_WAIT              ) \
        X(233, epoll_ctl,               EPOLL_CTL               ) \
        X(234, tgkill,                  TGKILL                  ) \
        X(235, utimes,                  UTIMES                  ) \
        X(236, vserver,                 VSERVER                 ) \
        X(237, mbind,                   MBIND                   ) \
        X(238, set_mempolicy,           SET_MEMPOLICY           ) \
        X(239, get_mempolicy,           GET_MEMPOLICY           ) \
        X(240, mq_open,                 MQ_OPEN                 ) \
        X(241, mq_unlink,               MQ_UNLINK               ) \
        X(242, mq_timedsend,            MQ_TIMEDSEND            ) \
        X(243, mq_timedreceive,         MQ_TIMEDRECEIVE         ) \
        X(244, mq_notify,               MQ_NOTIFY               ) \
        X(245, mq_getsetattr,           MQ_GETSETATTR           ) \
        X(246, kexec_load,              KEXEC_LOAD              ) \
        X(247, waitid,                  WAITID                  ) \
        X(248, add_key,                 ADD_KEY                 ) \
        X(249, request_key,             REQUEST_KEY             ) \
        X(250, keyctl,                  KEYCTL                  ) \
        X(251, ioprio_set,              IOPRIO_SET              ) \
        X(252, ioprio_get,              IOPRIO_GET              ) \
        X(253, inotify_init,            INOTIFY_INIT            ) \
        X(254, inotify_add_watch,       INOTIFY_ADD_WATCH       ) \
        X(255, inotify_rm_watch,        INOTIFY_RM_WATCH        ) \
        X(256, migrate_pages,           MIGRATE_PAGES           ) \
        X(257, openat,                  OPENAT                  ) \
        X(258, mkdirat,                 MKDIRAT                 ) \
        X(259, mknodat,                 MKNODAT                 ) \
        X(260, fchownat,                FCHOWNAT                ) \
        X(261, futimesat,               FUTIMESAT               ) \
        X(262, newfstatat,              NEWFSTATAT              ) \
        X(263, unlinkat,                UNLINKAT                ) \
        X(264, renameat,                RENAMEAT                ) \
        X(265, linkat,                  LINKAT                  ) \
        X(266, symlinkat,               SYMLINKAT               ) \
        X(267, readlinkat,              READLINKAT              ) \
        X(268, fchmodat,                FCHMODAT                ) \
        X(269, faccessat,               FACCESSAT               ) \
        X(270, pselect6,                PSELECT6                ) \
        X(271, ppoll,                   PPOLL                   ) \
        X(272, unshare,                 UNSHARE                 ) \
        X(273, set_robust_list,         SET_ROBUST_LIST         ) \
        X(274, get_robust_list,         GET_ROBUST_LIST         ) \
        X(275, splice,                  SPLICE                  ) \
        X(276, tee,                     TEE                     ) \
        X(277, sync_file_range,         SYNC_FILE_RANGE         ) \
        X(278, vmsplice,                VMSPLICE                ) \
        X(279, move_pages,              MOVE_PAGES              ) \
        X(280, utimensat,               UTIMENSAT               ) \
        X(281, epoll_pwait,             EPOLL_PWAIT             ) \
        X(282, signalfd,                SIGNALFD                ) \
        X(283, timerfd_create,          TIMERFD_CREATE          ) \
        X(284, eventfd,                 EVENTFD                 ) \
        X(285, fallocate,               FALLOCATE               ) \
        X(286, timerfd_settime,         TIMERFD_SETTIME         ) \
        X(287, timerfd_gettime,         TIMERFD_GETTIME         ) \
        X(288, accept4,                 ACCEPT4                 ) \
        X(289, signalfd4,               SIGNALFD4               ) \
        X(290, eventfd2,                EVENTFD2                ) \
        X(291, epoll_create1,           EPOLL_CREATE1           ) \
        X(292, dup3,                    DUP3                    ) \
        X(293, pipe2,                   PIPE2                   ) \
        X(294, inotify_init1,           INOTIFY_INIT1           ) \
        X(295, preadv,                  PREADV                  ) \
        X(296, pwritev,                 PWRITEV                 ) \
        X(297, rt_tgsigqueueinfo,       RT_TGSIGQUEUEINFO       ) \
        X(298, perf_event_open,         PERF_EVENT_OPEN         ) \
        X(299, recvmmsg,                RECVMMSG                ) \
        X(300, fanotify_init,           FANOTIFY_INIT           ) \
        X(301, fanotify_mark,           FANOTIFY_MARK           ) \
        X(302, prlimit64,               PRLIMIT64               ) \
        X(303, name_to_handle_at,       NAME_TO_HANDLE_AT       ) \
        X(304, open_by_handle_at,       OPEN_BY_HANDLE_AT       ) \
        X(305, clock_adjtime,           CLOCK_ADJTIME           ) \
        X(306, syncfs,                  SYNCFS                  ) \
        X(307, sendmmsg,                SENDMMSG                ) \
        X(308, setns,                   SETNS                   ) \
        X(309, getcpu,                  GETCPU                  ) \
        X(310, process_vm_readv,        PROCESS_VM_READV        ) \
        X(311, process_vm_writev,       PROCESS_VM_WRITEV       ) \
        X(312, kcmp,                    KCMP                    ) \
        X(313, finit_module,            FINIT_MODULE            ) \
        X(314, sched_setattr,           SCHED_SETATTR           ) \
        X(315, sched_getattr,           SCHED_GETATTR           ) \
        X(316, renameat2,               RENAMEAT2               ) \
        X(317, seccomp,                 SECCOMP                 ) \
        X(318, getrandom,               GETRANDOM               ) \
        X(319, memfd_create,            MEMFD_CREATE            ) \
        X(320, kexec_file_load,         KEXEC_FILE_LOAD         ) \
        X(321, bpf,                     BPF                     ) \
        X(322, execveat,                EXECVEAT                ) \
        X(323, userfaultfd,             USERFAULTFD             ) \
        X(324, membarrier,              MEMBARRIER              ) \
        X(325, mlock2,                  MLOCK2                  ) \
        X(326, copy_file_range,         COPY_FILE_RANGE         ) \
        X(327, preadv2,                 PREADV2                 ) \
        X(328, pwritev2,                PWRITEV2                ) \
        X(329, pkey_mprotect,           PKEY_MPROTECT           ) \
        X(330, pkey_alloc,              PKEY_ALLOC              ) \
        X(331, pkey_free,               PKEY_FREE               ) \
        X(332, statx,                   STATX                   ) \
        X(333, io_pgetevents,           IO_PGETEVENTS           ) \
        X(334, rseq,                    RSEQ                    ) \
        X(335, uretprobe,               URETPROBE               ) \
        X(336, uprobe,                  UPROBE                  ) \
        X(424, pidfd_send_signal,       PIDFD_SEND_SIGNAL       ) \
        X(425, io_uring_setup,          IO_URING_SETUP          ) \
        X(426, io_uring_enter,          IO_URING_ENTER          ) \
        X(427, io_uring_register,       IO_URING_REGISTER       ) \
        X(428, open_tree,               OPEN_TREE               ) \
        X(429, move_mount,              MOVE_MOUNT              ) \
        X(430, fsopen,                  FSOPEN                  ) \
        X(431, fsconfig,                FSCONFIG                ) \
        X(432, fsmount,                 FSMOUNT                 ) \
        X(433, fspick,                  FSPICK                  ) \
        X(434, pidfd_open,              PIDFD_OPEN              ) \
        X(435, clone3,                  CLONE3                  ) \
        X(436, close_range,             CLOSE_RANGE             ) \
        X(437, openat2,                 OPENAT2                 ) \
        X(438, pidfd_getfd,             PIDFD_GETFD             ) \
        X(439, faccessat2,              FACCESSAT2              ) \
        X(440, process_madvise,         PROCESS_MADVISE         ) \
        X(441, epoll_pwait2,            EPOLL_PWAIT2            ) \
        X(442, mount_setattr,           MOUNT_SETATTR           ) \
        X(443, quotactl_fd,             QUOTACTL_FD             ) \
        X(444, landlock_create_ruleset, LANDLOCK_CREATE_RULESET ) \
        X(445, landlock_add_rule,       LANDLOCK_ADD_RULE       ) \
        X(446, landlock_restrict_self,  LANDLOCK_RESTRICT_SELF  ) \
        X(447, memfd_secret,            MEMFD_SECRET            ) \
        X(448, process_mrelease,        PROCESS_MRELEASE        ) \
        X(449, futex_waitv,             FUTEX_WAITV             ) \
        X(450, set_mempolicy_home_node, SET_MEMPOLICY_HOME_NODE ) \
        X(451, cachestat,               CACHESTAT               ) \
        X(452, fchmodat2,               FCHMODAT2               ) \
        X(453, map_shadow_stack,        MAP_SHADOW_STACK        ) \
        X(454, futex_wake,              FUTEX_WAKE              ) \
        X(455, futex_wait,              FUTEX_WAIT              ) \
        X(456, futex_requeue,           FUTEX_REQUEUE           ) \
        X(457, statmount,               STATMOUNT               ) \
        X(458, listmount,               LISTMOUNT               ) \
        X(459, lsm_get_self_attr,       LSM_GET_SELF_ATTR       ) \
        X(460, lsm_set_self_attr,       LSM_SET_SELF_ATTR       ) \
        X(461, lsm_list_modules,        LSM_LIST_MODULES        ) \
        X(462, mseal,                   MSEAL                   ) \
        X(463, setxattrat,              SETXATTRAT              ) \
        X(464, getxattrat,              GETXATTRAT              ) \
        X(465, listxattrat,             LISTXATTRAT             ) \
        X(466, removexattrat,           REMOVEXATTRAT           ) \
        X(467, open_tree_attr,          OPEN_TREE_ATTR          ) \
        X(468, file_getattr,            FILE_GETATTR            ) \
        X(469, file_setattr,            FILE_SETATTR            ) \
        X(470, listns,                  LISTNS                  ) \
        X(471, rseq_slice_yield,        RSEQ_SLICE_YIELD        )

/* from /usr/include/bits/fcntl-linux.h  */
/* from musl-1.2.6/arch/generic/bits/fcntl.h */
#define OPEN_FLAGS \
    X(RDONLY,            00) \
    X(WRONLY,            01) \
    X(RDWR,              02) \
    X(CREAT,           0100) \
    X(EXCL,            0200) \
    X(NOCTTY,          0400) \
    X(TRUNC,          01000) \
    X(APPEND,         02000) \
    X(NONBLOCK,       04000) \
    X(DSYNC,         010000) \
    X(SYNC,        04010000) \
    X(RSYNC,       04010000) \
    X(DIRECTORY,    0200000) \
    X(NOFOLLOW,     0400000) \
    X(CLOEXEC,     02000000)



/* from /usr/include/bits/mman-linux.h */
#define MMAP_PROTECTIONS \
    X(NONE,     0) \
    X(READ,     1) \
    X(WRITE,    2) \
    X(EXECUTE,  4)

/* from /usr/include/bits/mman-linux.h */
#define MMAP_FLAGS \
    X(FILE,            0x00) /* File-backed pages */ \
    X(SHARED,          0x01) /* Share changes.  */ \
    X(PRIVATE,         0x02) /* Changes are private.  */ \
    X(SHARED_VALIDATE, 0x03) /* Share changes and validate extension flags.  */ \
    X(DROPPABLE,       0x08) /* Zero memory under memory pressure.  */ \
    X(FIXED,           0x10) /* Interpret addr exactly.  */ \
    X(ANONYMOUS,       0x20) /* Don't use a file.  */

#endif /* STD_LINUX_TABLES_H */