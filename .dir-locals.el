;;; Directory Local Variables
;;; For more information see (info "(emacs) Directory Variables")

((nil . ((eval . (setq compile-command
		       ;; FIXME: only set to this if it's not already
		       ;; set. Don't want to clear command
		       (format "cd %s && make"
			       (projectile-project-root))))))
 (c-mode . ((eval . (setq flycheck-clang-args (list "-nostdinc")))
	    (eval . (setq flycheck-clang-include-path (list "/usr/share/sdcc/include"))))))

