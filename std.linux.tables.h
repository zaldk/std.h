#ifndef STD_LINUX_TABLES_H
#define STD_LINUX_TABLES_H
// from linux-7.2/arch/x86/entry/syscalls/syscall_64.tbl
// the 'x32' entries are removed and the abi '64' is now 'x64'
// the format is: <syscall number> <name> <name in uppercase>
// a comment inside a macro must be a block comment, a `//` would eat the `\`
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

// from linux-7.2/include/uapi/asm-generic/errno.h
#define ERRNO_TABLE \
    X(EPERM,           1,   "Operation not permitted") \
    X(ENOENT,          2,   "No such file or directory") \
    X(ESRCH,           3,   "No such process") \
    X(EINTR,           4,   "Interrupted system call") \
    X(EIO,             5,   "I/O error") \
    X(ENXIO,           6,   "No such device or address") \
    X(E2BIG,           7,   "Argument list too long") \
    X(ENOEXEC,         8,   "Exec format error") \
    X(EBADF,           9,   "Bad file number") \
    X(ECHILD,          10,  "No child processes") \
    X(EAGAIN,          11,  "Try again") \
    X(ENOMEM,          12,  "Out of memory") \
    X(EACCES,          13,  "Permission denied") \
    X(EFAULT,          14,  "Bad address") \
    X(ENOTBLK,         15,  "Block device required") \
    X(EBUSY,           16,  "Device or resource busy") \
    X(EEXIST,          17,  "File exists") \
    X(EXDEV,           18,  "Cross-device link") \
    X(ENODEV,          19,  "No such device") \
    X(ENOTDIR,         20,  "Not a directory") \
    X(EISDIR,          21,  "Is a directory") \
    X(EINVAL,          22,  "Invalid argument") \
    X(ENFILE,          23,  "File table overflow") \
    X(EMFILE,          24,  "Too many open files") \
    X(ENOTTY,          25,  "Not a typewriter") \
    X(ETXTBSY,         26,  "Text file busy") \
    X(EFBIG,           27,  "File too large") \
    X(ENOSPC,          28,  "No space left on device") \
    X(ESPIPE,          29,  "Illegal seek") \
    X(EROFS,           30,  "Read-only file system") \
    X(EMLINK,          31,  "Too many links") \
    X(EPIPE,           32,  "Broken pipe") \
    X(EDOM,            33,  "Math argument out of domain of func") \
    X(ERANGE,          34,  "Math result not representable") \
    X(EDEADLK,         35,  "Resource deadlock would occur") \
    X(ENAMETOOLONG,    36,  "File name too long") \
    X(ENOLCK,          37,  "No record locks available") \
    X(ENOSYS,          38,  "Invalid system call number") \
    X(ENOTEMPTY,       39,  "Directory not empty") \
    X(ELOOP,           40,  "Too many symbolic links encountered") \
    /* X(EWOULDBLOCK,     11,  "Operation would block") */ \
    X(ENOMSG,          42,  "No message of desired type") \
    X(EIDRM,           43,  "Identifier removed") \
    X(ECHRNG,          44,  "Channel number out of range") \
    X(EL2NSYNC,        45,  "Level 2 not synchronized") \
    X(EL3HLT,          46,  "Level 3 halted") \
    X(EL3RST,          47,  "Level 3 reset") \
    X(ELNRNG,          48,  "Link number out of range") \
    X(EUNATCH,         49,  "Protocol driver not attached") \
    X(ENOCSI,          50,  "No CSI structure available") \
    X(EL2HLT,          51,  "Level 2 halted") \
    X(EBADE,           52,  "Invalid exchange") \
    X(EBADR,           53,  "Invalid request descriptor") \
    X(EXFULL,          54,  "Exchange full") \
    X(ENOANO,          55,  "No anode") \
    X(EBADRQC,         56,  "Invalid request code") \
    X(EBADSLT,         57,  "Invalid slot") \
    /* X(EDEADLOCK,       35,  "Deadlock") */ \
    X(EBFONT,          59,  "Bad font file format") \
    X(ENOSTR,          60,  "Device not a stream") \
    X(ENODATA,         61,  "No data available") \
    X(ETIME,           62,  "Timer expired") \
    X(ENOSR,           63,  "Out of streams resources") \
    X(ENONET,          64,  "Machine is not on the network") \
    X(ENOPKG,          65,  "Package not installed") \
    X(EREMOTE,         66,  "Object is remote") \
    X(ENOLINK,         67,  "Link has been severed") \
    X(EADV,            68,  "Advertise error") \
    X(ESRMNT,          69,  "Srmount error") \
    X(ECOMM,           70,  "Communication error on send") \
    X(EPROTO,          71,  "Protocol error") \
    X(EMULTIHOP,       72,  "Multihop attempted") \
    X(EDOTDOT,         73,  "RFS specific error") \
    X(EBADMSG,         74,  "Not a data message") \
    /* X(EFSBADCRC,       74,  "Bad CRC detected") */ \
    X(EOVERFLOW,       75,  "Value too large for defined data type") \
    X(ENOTUNIQ,        76,  "Name not unique on network") \
    X(EBADFD,          77,  "File descriptor in bad state") \
    X(EREMCHG,         78,  "Remote address changed") \
    X(ELIBACC,         79,  "Can not access a needed shared library") \
    X(ELIBBAD,         80,  "Accessing a corrupted shared library") \
    X(ELIBSCN,         81,  ".lib section in a.out corrupted") \
    X(ELIBMAX,         82,  "Attempting to link in too many shared libraries") \
    X(ELIBEXEC,        83,  "Cannot exec a shared library directly") \
    X(EILSEQ,          84,  "Illegal byte sequence") \
    X(ERESTART,        85,  "Interrupted system call should be restarted") \
    X(ESTRPIPE,        86,  "Streams pipe error") \
    X(EUSERS,          87,  "Too many users") \
    X(ENOTSOCK,        88,  "Socket operation on non-socket") \
    X(EDESTADDRREQ,    89,  "Destination address required") \
    X(EMSGSIZE,        90,  "Message too long") \
    X(EPROTOTYPE,      91,  "Protocol wrong type for socket") \
    X(ENOPROTOOPT,     92,  "Protocol not available") \
    X(EPROTONOSUPPORT, 93,  "Protocol not supported") \
    X(ESOCKTNOSUPPORT, 94,  "Socket type not supported") \
    X(EOPNOTSUPP,      95,  "Operation not supported on transport endpoint") \
    X(EPFNOSUPPORT,    96,  "Protocol family not supported") \
    X(EAFNOSUPPORT,    97,  "Address family not supported by protocol") \
    X(EADDRINUSE,      98,  "Address already in use") \
    X(EADDRNOTAVAIL,   99,  "Cannot assign requested address") \
    X(ENETDOWN,        100, "Network is down") \
    X(ENETUNREACH,     101, "Network is unreachable") \
    X(ENETRESET,       102, "Network dropped connection because of reset") \
    X(ECONNABORTED,    103, "Software caused connection abort") \
    X(ECONNRESET,      104, "Connection reset by peer") \
    X(ENOBUFS,         105, "No buffer space available") \
    X(EISCONN,         106, "Transport endpoint is already connected") \
    X(ENOTCONN,        107, "Transport endpoint is not connected") \
    X(ESHUTDOWN,       108, "Cannot send after transport endpoint shutdown") \
    X(ETOOMANYREFS,    109, "Too many references: cannot splice") \
    X(ETIMEDOUT,       110, "Connection timed out") \
    X(ECONNREFUSED,    111, "Connection refused") \
    X(EHOSTDOWN,       112, "Host is down") \
    X(EHOSTUNREACH,    113, "No route to host") \
    X(EALREADY,        114, "Operation already in progress") \
    X(EINPROGRESS,     115, "Operation now in progress") \
    X(ESTALE,          116, "Stale file handle") \
    X(EUCLEAN,         117, "Structure needs cleaning") \
    /* X(EFSCORRUPTED,    117, "Filesystem is corrupted") */ \
    X(ENOTNAM,         118, "Not a XENIX named type file") \
    X(ENAVAIL,         119, "No XENIX semaphores available") \
    X(EISNAM,          120, "Is a named type file") \
    X(EREMOTEIO,       121, "Remote I/O error") \
    X(EDQUOT,          122, "Quota exceeded") \
    X(ENOMEDIUM,       123, "No medium found") \
    X(EMEDIUMTYPE,     124, "Wrong medium type") \
    X(ECANCELED,       125, "Operation Canceled") \
    X(ENOKEY,          126, "Required key not available") \
    X(EKEYEXPIRED,     127, "Key has expired") \
    X(EKEYREVOKED,     128, "Key has been revoked") \
    X(EKEYREJECTED,    129, "Key was rejected by service") \
    X(EOWNERDEAD,      130, "Owner died") \
    X(ENOTRECOVERABLE, 131, "State not recoverable") \
    X(ERFKILL,         132, "Operation not possible due to RF-kill") \
    X(EHWPOISON,       133, "Memory page has hardware error") \
    X(EFTYPE,          134, "Wrong file type for the intended operation")

#define SIGNAL_CODES \
    X(HUP,    1) \
    X(INT,    2) \
    X(QUIT,   3) \
    X(ILL,    4) \
    X(TRAP,   5) \
    X(ABRT,   6) \
    X(IOT,    6) \
    X(BUS,    7) \
    X(FPE,    8) \
    X(KILL,   9) \
    X(USR1,   10) \
    X(SEGV,   11) \
    X(USR2,   12) \
    X(PIPE,   13) \
    X(ALRM,   14) \
    X(TERM,   15) \
    X(STKFLT, 16) \
    X(CHLD,   17) \
    X(CONT,   18) \
    X(STOP,   19) \
    X(TSTP,   20) \
    X(TTIN,   21) \
    X(TTOU,   22) \
    X(URG,    23) \
    X(XCPU,   24) \
    X(XFSZ,   25) \
    X(VTALRM, 26) \
    X(PROF,   27) \
    X(WINCH,  28) \
    X(IO,     29) \
    X(PWR,    30) \
    X(SYS,    31)


#define CLOCK_TYPES \
    X(REALTIME,           0) \
    X(MONOTONIC,          1) \
    X(PROCESS_CPUTIME_ID, 2) \
    X(THREAD_CPUTIME_ID,  3) \
    X(MONOTONIC_RAW,      4) \
    X(REALTIME_COARSE,    5) \
    X(MONOTONIC_COARSE,   6) \
    X(BOOTTIME,           7) \
    X(REALTIME_ALARM,     8) \
    X(BOOTTIME_ALARM,     9)



// from /usr/include/bits/fcntl-linux.h
// from musl-1.2.6/arch/generic/bits/fcntl.h
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



// from /usr/include/bits/mman-linux.h
#define MMAP_PROTECTIONS \
    X(NONE,     0) \
    X(READ,     1) \
    X(WRITE,    2) \
    X(EXECUTE,  4)

// from /usr/include/bits/mman-linux.h
#define MMAP_FLAGS \
    X(FILE,            0x00) /* File-backed pages */ \
    X(SHARED,          0x01) /* Share changes.  */ \
    X(PRIVATE,         0x02) /* Changes are private.  */ \
    X(SHARED_VALIDATE, 0x03) /* Share changes and validate extension flags.  */ \
    X(DROPPABLE,       0x08) /* Zero memory under memory pressure.  */ \
    X(FIXED,           0x10) /* Interpret addr exactly.  */ \
    X(ANONYMOUS,       0x20) /* Don't use a file.  */

// from /usr/include/bits/mman-linux.h
#define MADVISE_FLAGS \
    X(NORMAL,          0)   /* No further special treatment.  */ \
    X(RANDOM,          1)   /* Expect random page references.  */ \
    X(SEQUENTIAL,      2)   /* Expect sequential page references.  */ \
    X(WILLNEED,        3)   /* Will need these pages.  */ \
    X(DONTNEED,        4)   /* Don't need these pages.  */ \
    X(FREE,            8)   /* Free pages only if memory pressure.  */ \
    X(REMOVE,          9)   /* Remove these pages and resources.  */ \
    X(DONTFORK,        10)  /* Do not inherit across fork.  */ \
    X(DOFORK,          11)  /* Do inherit across fork.  */ \
    X(MERGEABLE,       12)  /* KSM may merge identical pages.  */ \
    X(UNMERGEABLE,     13)  /* KSM may not merge identical pages.  */ \
    X(HUGEPAGE,        14)  /* Worth backing with hugepages.  */ \
    X(NOHUGEPAGE,      15)  /* Not worth backing with hugepages.  */ \
    X(DONTDUMP,        16)  /* Explicitly exclude from the core dump, overrides the coredump filter bits.  */ \
    X(DODUMP,          17)  /* Clear the MADV_DONTDUMP flag.  */ \
    X(WIPEONFORK,      18)  /* Zero memory on fork, child only.  */ \
    X(KEEPONFORK,      19)  /* Undo MADV_WIPEONFORK.  */ \
    X(COLD,            20)  /* Deactivate these pages.  */ \
    X(PAGEOUT,         21)  /* Reclaim these pages.  */ \
    X(POPULATE_READ,   22)  /* Populate (prefault) page tables readable.  */ \
    X(POPULATE_WRITE,  23)  /* Populate (prefault) page tables writable.  */ \
    X(DONTNEED_LOCKED, 24)  /* Like MADV_DONTNEED, but drop locked pages too.  */ \
    X(COLLAPSE,        25)  /* Synchronous hugepage collapse.  */ \
    X(HWPOISON,        100) /* Poison a page for testing.  */ \
    X(GUARD_INSTALL,   102) /* Fatal signal on access to range */ \
    X(GUARD_REMOVE,    103) /* Unguard range */


// from usr/include/linux/mman.h
#define MREMAP_FLAGS \
    X(MAYMOVE,   1) \
    X(FIXED,     2) \
    X(DONTUNMAP, 4)

#define DIR_ENTRY_TYPES \
    X(UNKNOWN,          0x0) \
    X(NAMED_PIPE,       0x1)   /* FIFO */ \
    X(CHARACTER_DEVICE, 0x2) \
    X(DIRECTORY,        0x4) \
    X(BLOCK_DEVICE,     0x6) \
    X(REGULAR_FILE,     0x8) \
    X(SYMBOLIC_LINK,    0xa) \
    X(SOCKET,           0xc)   /* UNIX domain socket */

#endif // STD_LINUX_TABLES_H
