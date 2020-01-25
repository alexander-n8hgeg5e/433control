# Copyright 1999-2018 Gentoo Foundation
# Distributed under the terms of the GNU General Public License v2
EAPI=6

LICENSE=""

PYTHON_COMPAT=( python3_{5,6} )
EGIT_REPO_URI="${CODEDIR}/${PN} ${MYGITHUB_URIBASE}${PN}.git"
inherit git-r3 python-r1

DESCRIPTION="control the stuff in the house "
HOMEPAGE=""

LICENSE=""
SLOT="0"
KEYWORDS="~amd64 ~x86"
IUSE=""

DEPEND=""
RDEPEND="${DEPEND} \
	dev-python/pyserial[$(python_gen_usedep 'python3*')]\
	"

src_install(){
dobin transmit_serial/rfcc
dobin transmit_serial/rf
dobin transmit_serial/gpio
dodir /usr/share/433control
insinto /usr/share/433control
doins record_codes/datacapture_fb1_1_off
doins record_codes/datacapture_fb1_1_on
doins record_codes/datacapture_fb1_2_off
doins record_codes/datacapture_fb1_2_on
doins record_codes/datacapture_fb1_3_off
doins record_codes/datacapture_fb1_3_on
doins record_codes/datacapture_fb1_4_off
doins record_codes/datacapture_fb1_4_on
doins record_codes/datacapture_fb1_all_off
doins record_codes/datacapture_fb1_all_on
doins record_codes/datacapture_fb2_1_off
doins record_codes/datacapture_fb2_1_on
doins record_codes/datacapture_fb2_2_off
doins record_codes/datacapture_fb2_2_on
doins record_codes/datacapture_fb2_3_off
doins record_codes/datacapture_fb2_3_on
doins record_codes/datacapture_fb2_4_off
doins record_codes/datacapture_fb2_4_on
doins record_codes/datacapture_fb2_all_off
doins record_codes/datacapture_fb2_all_on
	}
