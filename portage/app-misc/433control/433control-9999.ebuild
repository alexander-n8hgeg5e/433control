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
dobin transmitter/rfcc
dobin transmitter/rf
dobin transmitter/ir
dobin transmitter/gpio
dodir /usr/share/433control
insinto /usr/share/433control
doins codes/433/remote1_btn1_off
doins codes/433/remote1_btn1_on
doins codes/433/remote1_btn2_off
doins codes/433/remote1_btn2_on
doins codes/433/remote1_btn3_off
doins codes/433/remote1_btn3_on
doins codes/433/remote1_btn4_off
doins codes/433/remote1_btn4_on
doins codes/433/remote1_btnall_off
doins codes/433/remote1_btnall_on
doins codes/433/remote2_btn1_off
doins codes/433/remote2_btn1_on
doins codes/433/remote2_btn2_off
doins codes/433/remote2_btn2_on
doins codes/433/remote2_btn3_off
doins codes/433/remote2_btn3_on
doins codes/433/remote2_btn4_off
doins codes/433/remote2_btn4_on
doins codes/433/remote2_btnall_off
doins codes/433/remote2_btnall_on
	}
