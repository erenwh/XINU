
;; Options Menu Settings
;; =====================
(cond
 ((and (string-match "XEmacs" emacs-version)
       (boundp 'emacs-major-version)
       (or (and
            (= emacs-major-version 19)
            (>= emacs-minor-version 14))
           (= emacs-major-version 20))
       (fboundp 'load-options-file))
  (load-options-file "/homes/grr/.xemacs-options")))
;; ============================
;; End of Options Menu Settings

(if (file-exists-p "~/.emacs_local")    (load-file "~/.emacs_local"))
(if (file-exists-p "~/emacs/muckel.el") (load "~/emacs/muckel"))
(if (file-exists-p "~/emacs/cew.el")    (load "~/emacs/cew"))

(load "font-lock")

;----------------------------------------------------------------------------
; Stuff for font-lock-mode
;----------------------------------------------------------------------------
    (progn
      (setq visible-bell nil)

      (defun set-background-light ()
	"Set background color to a light color"
	(interactive)
	(set-face-background 'highlight			"darkgreen")
	(set-face-foreground 'highlight			"antique white")
	(set-face-background 'primary-selection		"navyblue")
	(set-face-foreground 'primary-selection		"antique white")
	(set-face-background 'secondary-selection	"maroon")
	(set-face-foreground 'secondary-selection	"antique white")
	(set-face-background 'isearch			"firebrick4")
	(set-face-foreground 'isearch			"antique white")
	(set-face-foreground 'modeline			"antique white")
	(set-face-background 'modeline			"black")
	(set-face-foreground 'default			"black")
	(set-face-background 'default			"antique white")

	(font-lock-use-default-colors)
	)

      (defun set-background-dark ()
	"Set background color to a dark color"
	(interactive)
	(set-face-background 'highlight			"antique white")
	(set-face-foreground 'highlight			"darkgreen")
	(set-face-background 'primary-selection		"antique white")
	(set-face-foreground 'primary-selection		"navyblue")
	(set-face-background 'secondary-selection	"antique white")
	(set-face-foreground 'secondary-selection	"maroon")
	(set-face-background 'isearch			"antique white")
	(set-face-foreground 'isearch			"firebrick4")
	(set-face-foreground 'modeline			"black")
	(set-face-background 'modeline			"antique white")
	(set-face-foreground 'default			"antique white")
	(set-face-background 'default			"black")

	(font-lock-use-default-colors)
	(set-face-foreground 'font-lock-comment-face	"plum1")
	(set-face-foreground 'font-lock-string-face	"green2")
	(set-face-foreground 'font-lock-doc-string-face "palegreen")
	(set-face-foreground 'font-lock-function-name-face "yellow")
	(set-face-foreground 'font-lock-keyword-face	"deep sky blue")
	(set-face-foreground 'font-lock-type-face	"red")
	)

      (defun set-screen-background (color)
	"Set background color for only the current screen"
	(interactive "sColor? ")
	(set-face-background 'default color (selected-screen))
	)

      (defun set-font-lock-mode (val)
	(interactive "nValue? ")
	(font-lock-mode val)
	)

      (defun font-lock-mode-on ()
	(interactive)
	(font-lock-mode 2)
	)

      (defun font-lock-mode-off ()
	(interactive)
	(font-lock-mode 0)
	)

      (set-background-dark)

      (setq x-pointer-background-color "red")
)

;---------------------------------------------------------------------------
; Other various bindings
;---------------------------------------------------------------------------
(global-set-key "\C-m" 'newline-and-indent)
(global-set-key "\e1" 'delete-other-windows)
(global-set-key "\e2" 'split-window)
(global-set-key "\ed" 'kill-current-buffer)
(global-set-key "\eg" 'goto-line)
(global-set-key "\eh" 'backward-kill-word)
(global-set-key "\C-xu" 'undo)
(global-set-key "\C-v" 'cew-next-page)
(global-set-key "\ev" 'cew-previous-page)
(global-set-key "\C-xn" 'other-window)
(global-set-key "\C-xp" 'cew-previous-window)
(global-set-key "\C-x\C-u" 'undo-mode)
(global-set-key "\C-x\C-m" 'local-mh-rmail)
;(global-set-key "\C-x\C-s" 'shell)
(global-set-key "\e" 'save-all-buffers)
(global-set-key "\C-o" 'open-next-line-and-indent)
(global-set-key "\C-f" 'isearch-forward)
(global-set-key "\e1" 'x-copy-primary-selection)
(global-set-key "\e2" 'x-kill-primary-selection)
(global-set-key "\e3" 'x-yank-clipboard-selection)

;---------------------------------------------------------------------------
; General Emacs stuff
;---------------------------------------------------------------------------
(setq make-backup-files nil)
(setq lock-directory nil)
(setq ask-about-buffer-names t)
(setq delete-auto-save-files t)
(setq auto-save-interval 2000)
(setq-default truncate-lines nil)
(setq-default compile-command "gnumake install")
(fset 'help-prefix help-map)
(setq tab-stop-list (list 8 16 24 32 40 48 56 64 72))
(setq next-line-add-newlines nil)
(setq c-basic-offset 8)
(setq c-indent-level 8)
;(set-variable c-basic-offset 8)
(setq delete-auto-save-files t)


